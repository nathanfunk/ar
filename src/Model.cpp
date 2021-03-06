/*
	Model.cpp

		Abstract base class for a model. The specific extended class will render the given model. 

	Author:	Brett Porter
	Email: brettporter@yahoo.com
	Website: http://www.geocities.com/brettporter/
	Copyright (C)2000, Brett Porter. All Rights Reserved.
	Conversion to GLUT done by Rocco Balsamo, http://www.roccobalsamo.com
	This file may be used only as long as this copyright notice remains intact.
*/

#include <stdlib.h>
#include <gl\glut.h>			// Header File For The OpenGL32 Library
#include <gl\glaux.h>
#include "Model.h"
#include "textureloader.h"
//#include "debug.h"
#include "Win32Timer.h"
#include <iostream>
#include <Assert.h>

//#include "Tga.h"
//GLuint LoadTGA(char * filename);

#pragma unmanaged

Model::Model()
{
	m_numMeshes = 0;
	m_pMeshes = NULL;
	m_numMaterials = 0;
	m_pMaterials = NULL;
	m_numTriangles = 0;
	m_pTriangles = NULL;
	m_numVertices = 0;
	m_pVertices = NULL;

// { NEW } 
	m_numJoints = 0;
	m_pJoints = NULL;

	m_pTimer = Timer::getNewTimer();
	m_looping = true;

	frame1 = 0; frame2 = 0;animFPS=0;
	restart();
	// { end NEW } 

}

Model::~Model()
{
	int i;
	for ( i = 0; i < m_numMeshes; i++ )
		delete[] m_pMeshes[i].m_pTriangleIndices;
	for ( i = 0; i < m_numMaterials; i++ )
		delete[] m_pMaterials[i].m_pTextureFilename;

	m_numMeshes = 0;
	if ( m_pMeshes != NULL )
	{
		delete[] m_pMeshes;
		m_pMeshes = NULL;
	}

	m_numMaterials = 0;
	if ( m_pMaterials != NULL )
	{
		delete[] m_pMaterials;
		m_pMaterials = NULL;
	}

	m_numTriangles = 0;
	if ( m_pTriangles != NULL )
	{
		delete[] m_pTriangles;
		m_pTriangles = NULL;
	}

	m_numVertices = 0;
	if ( m_pVertices != NULL )
	{
		delete[] m_pVertices;
		m_pVertices = NULL;
	}
}

/*
void Model::setupJoints() 
{
   int i;
   for ( i = 0; i < m_numJoints; i++ ) {
      Joint& joint = m_pJoints[i];

      joint.m_relative.setRotationRadians( joint.m_localRotation );
      joint.m_relative.setTranslation( joint.m_localTranslation );
      if ( joint.m_parent != -1 ) {
         joint.m_absolute.set( m_pJoints[joint.m_parent].m_absolute.getMatrix());
         joint.m_absolute.postMultiply( joint.m_relative );
      }
      else
         joint.m_absolute.set( joint.m_relative.getMatrix());
   }
	for ( i = 0; i < m_numVertices; i++ ) {
      Vertex& vertex = m_pVertices[i];

      if ( vertex.m_boneID != -1 ) {
		  const PL3D::Matrix& matrix = m_pJoints[vertex.m_boneID].m_absolute;

         matrix.inverseTranslateVect( vertex.m_location );
         matrix.inverseRotateVect( vertex.m_location );
      }
   }

 for ( i = 0; i < m_numTriangles; i++ ) {
      Triangle& triangle = m_pTriangles[i];

      for ( int j = 0; j < 3; j++ ) {
         const Vertex& vertex = m_pVertices[triangle.m_vertexIndices[j]];
         if ( vertex.m_boneID != -1 ) {
			 const PL3D::Matrix& matrix = m_pJoints[vertex.m_boneID].m_absolute;

            matrix.inverseRotateVect( triangle.m_vertexNormals[j] );
         }
      }
 }


}
*/
void Model::draw(int advance) 
{

	//glRotatef(90,1,0,0);
	//glTranslatef(0,-20,0);
	//glScalef(1,1,1);
	//glutSolidCube(50.0);
	//return;
				// { NEW }
	if (advance == 1)
		advanceAnimation();
					// { end NEW }
	GLboolean texEnabled = glIsEnabled( GL_TEXTURE_2D );

	

	// Draw by group
	for ( int i = 0; i < m_numMeshes; i++ )
	{
		int materialIndex = m_pMeshes[i].m_materialIndex;
		if ( materialIndex >= 0 )
		{
			glMaterialfv( GL_FRONT, GL_AMBIENT, m_pMaterials[materialIndex].m_ambient );
			glMaterialfv( GL_FRONT, GL_DIFFUSE, m_pMaterials[materialIndex].m_diffuse );
			glMaterialfv( GL_FRONT, GL_SPECULAR, m_pMaterials[materialIndex].m_specular );
			glMaterialfv( GL_FRONT, GL_EMISSION, m_pMaterials[materialIndex].m_emissive );
			glMaterialf( GL_FRONT, GL_SHININESS, m_pMaterials[materialIndex].m_shininess );

			if ( m_pMaterials[materialIndex].m_texture > 0 )
			{
				glBindTexture( GL_TEXTURE_2D, m_pMaterials[materialIndex].m_texture );
				glEnable( GL_TEXTURE_2D );
			}
			else
				glDisable( GL_TEXTURE_2D );
		}
		else
		{
			// Material properties?
			glDisable( GL_TEXTURE_2D );
		}

		glBegin( GL_TRIANGLES );
		{
			for ( int j = 0; j < m_pMeshes[i].m_numTriangles; j++ )
			{
				int triangleIndex = m_pMeshes[i].m_pTriangleIndices[j];
				const Triangle* pTri = &m_pTriangles[triangleIndex];

				for ( int k = 0; k < 3; k++ )
				{
					int index = pTri->m_vertexIndices[k];
					
					// { NEW }
					if ( m_pVertices[index].m_boneID == -1 )
					{
						// same as before
						glTexCoord2f( pTri->m_s[k], pTri->m_t[k] );
						glNormal3fv( pTri->m_vertexNormals[k] );
						glVertex3fv( m_pVertices[index].m_location );
					}
					else
					{

						//fprintf(stderr, "%d ", m_pVertices[index].m_boneID );
						// rotate according to transformation matrix
						const PL3D::Matrix& final = m_pJoints[m_pVertices[index].m_boneID].m_final;

						glTexCoord2f( pTri->m_s[k], pTri->m_t[k] );

						PL3D::Vector newNormal( pTri->m_vertexNormals[k] );
						//std::cin.ignore(); 
							//exit(1);
						//for (int k = 0;k<16; k++){
						//	fprintf(stderr, "%3.0f ", final.m_matrix[k]);
						//}



						newNormal.transform3( final );
						
						newNormal.normalize();
						
						glNormal3fv( newNormal.getVector());
						
						PL3D::Vector newVertex( m_pVertices[index].m_location );
						newVertex.transform( final );
						glVertex3fv( newVertex.getVector());
						
					}
					// { end NEW }



					//glNormal3fv( pTri->m_vertexNormals[k] );
					//glTexCoord2f( pTri->m_s[k], pTri->m_t[k] );
					//glVertex3fv( m_pVertices[index].m_location );
				}
			}
		}
		glEnd();
	}

	if ( texEnabled )
		glEnable( GL_TEXTURE_2D );
	else
		glDisable( GL_TEXTURE_2D );
}

void Model::reloadTextures()
{
	string fullpath;
	for ( int i = 0; i < m_numMaterials; i++ )
		if ( strlen( m_pMaterials[i].m_pTextureFilename ) > 0 ) {
			fullpath = m_path + m_pMaterials[i].m_pTextureFilename;
			m_pMaterials[i].m_texture = LoadGLTexture( fullpath.c_str() );
			//m_pMaterials[i].m_texture = LoadTGA( fullpath.c_str() );
		}
		else
			m_pMaterials[i].m_texture = 0;
}


// { NEW }
void Model::setJointKeyframe( int jointIndex, int keyframeIndex, float time, float *parameter, bool isRotation )
{
	assert( m_numJoints > jointIndex );

	Keyframe& keyframe = isRotation ? m_pJoints[jointIndex].m_pRotationKeyframes[keyframeIndex] :
		m_pJoints[jointIndex].m_pTranslationKeyframes[keyframeIndex];

	keyframe.m_jointIndex = jointIndex;
	keyframe.m_time = time;
	memcpy( keyframe.m_parameter, parameter, sizeof( float )*3 );

	//fprintf(stderr, "joint %d keyframe %d time %3.2f\n", jointIndex, keyframeIndex, time);
	

}

void Model::setupJoints()
{
	int i;
	for ( i = 0; i < m_numJoints; i++ )
	{
		Joint& joint = m_pJoints[i];

		joint.m_relative.setRotationRadians( joint.m_localRotation );
		joint.m_relative.setTranslation( joint.m_localTranslation );
		if ( joint.m_parent != -1 )
		{
			joint.m_absolute.set( m_pJoints[joint.m_parent].m_absolute.getMatrix());
			joint.m_absolute.postMultiply( joint.m_relative );
		}
		else
			joint.m_absolute.set( joint.m_relative.getMatrix());
	}

	for ( i = 0; i < m_numVertices; i++ )
	{
		Vertex& vertex = m_pVertices[i];

		if ( vertex.m_boneID != -1 )
		{
			const PL3D::Matrix& matrix = m_pJoints[vertex.m_boneID].m_absolute;

			matrix.inverseTranslateVect( vertex.m_location );
			matrix.inverseRotateVect( vertex.m_location );
		}
	}

	for ( i = 0; i < m_numTriangles; i++ ) {
		Triangle& triangle = m_pTriangles[i];
		for ( int j = 0; j < 3; j++ ) {
			const Vertex& vertex = m_pVertices[triangle.m_vertexIndices[j]];
			if ( vertex.m_boneID != -1 ) {
				const PL3D::Matrix& matrix = m_pJoints[vertex.m_boneID].m_absolute;
				matrix.inverseRotateVect( triangle.m_vertexNormals[j] );
			}
		}
	}
}

void Model::restart(){

m_totalTime = (frame2 - frame1)*1000.0/animFPS;
for ( int i = 0; i < m_numJoints; i++ )
	{
		m_pJoints[i].m_currentRotationKeyframe = frame1;
		m_pJoints[i].m_currentTranslationKeyframe = frame1;
		m_pJoints[i].m_final.set( m_pJoints[i].m_absolute.getMatrix());
	}
	m_pTimer->reset();
}


void Model::restart(int _frame1, int _frame2)
{
	frame1 = _frame1;
	frame2 = _frame2;

	m_totalTime = (frame2 - frame1)*1000.0/animFPS;
	double startTime = 0;
	for ( int i = 0; i < m_numJoints; i++ )
	{
		if (i == 0)
			startTime = m_pJoints[i].m_pTranslationKeyframes[frame1].m_time;
		if (startTime > m_pJoints[i].m_pTranslationKeyframes[frame1].m_time)
			startTime = m_pJoints[i].m_pTranslationKeyframes[frame1].m_time;
		m_pJoints[i].m_currentRotationKeyframe = frame1;
		m_pJoints[i].m_currentTranslationKeyframe = frame1;
		m_pJoints[i].m_final.set( m_pJoints[i].m_absolute.getMatrix());
	}

	//fprintf(stderr, "ReStartTime: %3.4f \n", startTime);
	m_pTimer->reset(startTime);
	//exit(1);
}

void Model::advanceAnimation()
{
	double time = m_pTimer->getTime();
	///fprintf(stderr, "Time: %3.0f ", time );

	if ( time > m_totalTime )
	{
		if ( m_looping )
		{
			restart(frame1, frame2);
			///std::cout<<"RESTARTING "<<std::endl;
			//fprintf(stderr, "
			//time = frame1*1000.0/animFPS;
			time = m_pTimer->getTime();
			//time = 0;
		}
		else
			time = m_totalTime;
	} 

	for ( int i = 0; i < m_numJoints; i++ )
	{
		float transVec[3];
		PL3D::Matrix transform;
		int frame;
		Joint *pJoint = &m_pJoints[i];


		if ( pJoint->m_numRotationKeyframes == 0 && pJoint->m_numTranslationKeyframes == 0 )
		{
			pJoint->m_final.set( pJoint->m_absolute.getMatrix());
			continue;
		}

		frame = pJoint->m_currentTranslationKeyframe;
		while ( frame < pJoint->m_numTranslationKeyframes && pJoint->m_pTranslationKeyframes[frame].m_time < time )
		{
			frame++;
			//std::cout<<"frame "<<frame<<" "<<std::endl;
		}
		pJoint->m_currentTranslationKeyframe = frame;

		if ( frame == 0 )
			memcpy( transVec, pJoint->m_pTranslationKeyframes[0].m_parameter, sizeof ( float )*3 );
		else if ( frame == pJoint->m_numTranslationKeyframes )
			memcpy( transVec, pJoint->m_pTranslationKeyframes[frame-1].m_parameter, sizeof ( float )*3 );
		else
		{
			assert (frame > 0 && frame < pJoint->m_numTranslationKeyframes );

			const Model::Keyframe& curFrame = pJoint->m_pTranslationKeyframes[frame];
			const Model::Keyframe& prevFrame = pJoint->m_pTranslationKeyframes[frame-1];

			float timeDelta = curFrame.m_time-prevFrame.m_time;
			float interpValue = ( float )(( time-prevFrame.m_time )/timeDelta );

			transVec[0] = prevFrame.m_parameter[0]+( curFrame.m_parameter[0]-prevFrame.m_parameter[0] )*interpValue;
			transVec[1] = prevFrame.m_parameter[1]+( curFrame.m_parameter[1]-prevFrame.m_parameter[1] )*interpValue;
			transVec[2] = prevFrame.m_parameter[2]+( curFrame.m_parameter[2]-prevFrame.m_parameter[2] )*interpValue; 
		}

		frame = pJoint->m_currentRotationKeyframe;
		while ( frame < pJoint->m_numRotationKeyframes && pJoint->m_pRotationKeyframes[frame].m_time < time )
		{
			frame++;
		}
		pJoint->m_currentRotationKeyframe = frame;

		if ( frame == 0 )
			transform.setRotationRadians( pJoint->m_pRotationKeyframes[0].m_parameter );
		else if ( frame == pJoint->m_numRotationKeyframes )
			transform.setRotationRadians( pJoint->m_pRotationKeyframes[frame-1].m_parameter );
		else
		{
			assert( frame > 0 && frame < pJoint->m_numRotationKeyframes );

			const Model::Keyframe& curFrame = pJoint->m_pRotationKeyframes[frame];
			const Model::Keyframe& prevFrame = pJoint->m_pRotationKeyframes[frame-1];
			
			float timeDelta = curFrame.m_time-prevFrame.m_time;
			float interpValue = ( float )(( time-prevFrame.m_time )/timeDelta );

			//fprintf(stderr, "framenum: %d curframe %3.2f prevframe %3.2f time %3.2f interp %3.2f\n", 
			//	frame, curFrame.m_time, prevFrame.m_time, time, interpValue);

			assert( interpValue >= 0 && interpValue <= 1 );

#if 0
			Quaternion qPrev( prevFrame.m_parameter );
			Quaternion qCur( curFrame.m_parameter );
			Quaternion qFinal( qPrev, qCur, interpValue );
			transform.setRotationQuaternion( qFinal );
#else
			float rotVec[3];

			rotVec[0] = prevFrame.m_parameter[0]+( curFrame.m_parameter[0]-prevFrame.m_parameter[0] )*interpValue;
			rotVec[1] = prevFrame.m_parameter[1]+( curFrame.m_parameter[1]-prevFrame.m_parameter[1] )*interpValue;
			rotVec[2] = prevFrame.m_parameter[2]+( curFrame.m_parameter[2]-prevFrame.m_parameter[2] )*interpValue;

			transform.setRotationRadians( rotVec );
#endif
		}

		transform.setTranslation( transVec );
		PL3D::Matrix relativeFinal( pJoint->m_relative );
		relativeFinal.postMultiply( transform );

		if ( pJoint->m_parent == -1 )
			pJoint->m_final.set( relativeFinal.getMatrix());
		else
		{
			pJoint->m_final.set( m_pJoints[pJoint->m_parent].m_final.getMatrix());
			pJoint->m_final.postMultiply( relativeFinal );
		}
	}

	
}
// { end NEW }