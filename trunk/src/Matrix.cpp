/*
	Matrix.cpp

		Matrix manipulation.

	Author:	Brett Porter
	Email: brettporter@yahoo.com
	Website: http://rsn.gamedev.net/pl3d
	Copyright (C)2000, 2001, Brett Porter. All Rights Reserved.
	This source code is released under the LGPL. See license.txt for details.

	Created: 9 December 2000

	Please see the file ChangeLog.html for a revision history.
*/
#include <memory.h>
#include "Timer.h"
#include "Matrix.h"


#pragma unmanaged



using namespace PL3D;


Matrix::Matrix()
{
	loadIdentity();
}

Matrix::~Matrix()
{
}

void Matrix::postMultiply( const Matrix& matrix )
{
	float newMatrix[16];
	const float *m1 = m_matrix, *m2 = matrix.m_matrix;

	newMatrix[0] = m1[0]*m2[0] + m1[4]*m2[1] + m1[8]*m2[2];
	newMatrix[1] = m1[1]*m2[0] + m1[5]*m2[1] + m1[9]*m2[2];
	newMatrix[2] = m1[2]*m2[0] + m1[6]*m2[1] + m1[10]*m2[2];
	newMatrix[3] = 0;

	newMatrix[4] = m1[0]*m2[4] + m1[4]*m2[5] + m1[8]*m2[6];
	newMatrix[5] = m1[1]*m2[4] + m1[5]*m2[5] + m1[9]*m2[6];
	newMatrix[6] = m1[2]*m2[4] + m1[6]*m2[5] + m1[10]*m2[6];
	newMatrix[7] = 0;

	newMatrix[8] = m1[0]*m2[8] + m1[4]*m2[9] + m1[8]*m2[10];
	newMatrix[9] = m1[1]*m2[8] + m1[5]*m2[9] + m1[9]*m2[10];
	newMatrix[10] = m1[2]*m2[8] + m1[6]*m2[9] + m1[10]*m2[10];
	newMatrix[11] = 0;

	newMatrix[12] = m1[0]*m2[12] + m1[4]*m2[13] + m1[8]*m2[14] + m1[12];
	newMatrix[13] = m1[1]*m2[12] + m1[5]*m2[13] + m1[9]*m2[14] + m1[13];
	newMatrix[14] = m1[2]*m2[12] + m1[6]*m2[13] + m1[10]*m2[14] + m1[14];
	newMatrix[15] = 1;

	set( newMatrix );
}

void Matrix::setTranslation( const float *translation )
{
	m_matrix[12] = translation[0];
	m_matrix[13] = translation[1];
	m_matrix[14] = translation[2];
}

void Matrix::translate( float x, float y, float z )
{
	m_matrix[12] += x;
	m_matrix[13] += y;
	m_matrix[14] += z;
}


void Matrix::setInverseTranslation( const float *translation )
{
	m_matrix[12] = -translation[0];
	m_matrix[13] = -translation[1];
	m_matrix[14] = -translation[2];
}

void Matrix::setRotationDegrees( const float *angles )
{
	float vec[3];
	vec[0] = ( float )( angles[0]*PI/180.0 );
	vec[1] = ( float )( angles[1]*PI/180.0 );
	vec[2] = ( float )( angles[2]*PI/180.0 );
	setRotationRadians( vec );
}

void Matrix::setRotationDegrees( float rX, float rY, float rZ)
{
	float vec[3];
	vec[0] = ( float )( rX*PI/180.0 );
	vec[1] = ( float )( rY*PI/180.0 );
	vec[2] = ( float )( rZ*PI/180.0 );
	setRotationRadians( vec );
}


void Matrix::setScale(float sX, float sY, float sZ){
	m_matrix[0] = sX;
	m_matrix[5] =  sY;
	m_matrix[10] =  sZ;
	m_matrix[15] =  1;
}


void Matrix::setRotationDegrees(float theta, float x, float y, float z)
{
//theta in degrees: convert to radians;
	float radians = ( float )( theta*PI/180.0 );
//normalize the vector
	float vMag = sqrt(x*x + y*y + z*z);
	if (vMag == 0 ) return;

	x = x/vMag; y = y/vMag; z = z/vMag;
	setRotationRadians(radians, x, y, z);
}




void Matrix::setRotationDegrees(float theta, float a, float b, float c,
								float u, float v, float w)
{
//theta in degrees: convert to radians;
	float radians = ( float )( theta*PI/180.0 );
//normalize the vector
	float vMag = sqrt(u*u + v*v + w*w);
	if (vMag == 0 ) return;

	u = u/vMag; v = v/vMag; w = w/vMag;
	setRotationRadians(radians, a,b,c, u, v, w);
}


void Matrix::setInverseRotationDegrees( const float *angles )
{
	float vec[3];
	vec[0] = ( float )( angles[0]*PI/180.0 );
	vec[1] = ( float )( angles[1]*PI/180.0 );
	vec[2] = ( float )( angles[2]*PI/180.0 );
	setInverseRotationRadians( vec );
}


//rotation about a line through point (a,b,c) parallel to <u,v,w>
void Matrix::setRotationRadians(float radians,  float a, float b, float c,
								float u, float v, float w)
{

	float cosine = cos(radians);
    float sine = sin(radians);
    float one_minus_cosine = 1 - cosine;
	float L2 = u*u + v*v + w*w;
	float L = sqrt(L2);
	float u2 = u*u;
	float v2 = v*v;
	float w2 = w*w;


	m_matrix[0] =  u2 + (v2+w2)*cosine;
	m_matrix[1] =  u*v*one_minus_cosine + w*L*sine;
	m_matrix[2] =  u*w*one_minus_cosine - v*L*sine;
	m_matrix[3] =  0;

	m_matrix[4] =  u*v*one_minus_cosine - w*L*sine;
	m_matrix[5] =  v2 +(u2+w2)*cosine;
	m_matrix[6] =  v*w*one_minus_cosine + u*L*sine;
	m_matrix[7] =  0;

	m_matrix[8] =  u*w*one_minus_cosine + v*L*sine;
	m_matrix[9] =  v*w*one_minus_cosine - u*L*sine;
	m_matrix[10] = w2 +(u2+v2)*cosine;
	m_matrix[11] = 0;

	m_matrix[12] = a*(v2+w2) - u*(b*v + c*w) + (u*(b*v+c*w)-a*(v2+w2))*cosine + (b*w - c*v)*L*sine;
	m_matrix[13] = b*(u2+w2) - v*(a*u + c*w) + (v*(a*u+c*w)-b*(u2+w2))*cosine + (c*u - a*w)*L*sine;
	m_matrix[14] = c*(u2+v2) - w*(a*u + b*v) + (w*(a*u+b*v)-c*(u2+v2))*cosine + (a*v - b*u)*L*sine;
	m_matrix[15] = 1;

}

void Matrix::setRotationRadians(float radians,  float x, float y, float z)
{


float cosine = cos(radians);
    float sine = sin(radians);
    float one_minus_cosine = 1 - cosine;


/*
M.x[0][0] = x * x + (1.0 - x * x) * cosine;
    M.x[0][1] = x * y * one_minus_cosine + z * sine;
    M.x[0][2] = x * z * one_minus_cosine - y * sine;
    M.x[0][3] = 0;

    M.x[1][0] = x * y * one_minus_cosine - z * sine;
    M.x[1][1] = y * y + (1.0 - y * y) * cosine;
    M.x[1][2] = y * z * one_minus_cosine + x * sine;
    M.x[1][3] = 0;

    M.x[2][0] = x * z * one_minus_cosine + y * sine;
    M.x[2][1] = y * z * one_minus_cosine - x * sine;
    M.x[2][2] = z * z + (1.0 - z * z) * cosine;
    M.x[2][3] = 0;

    M.x[3][0] = 0;
    M.x[3][1] = 0;
    M.x[3][2] = 0;
    M.x[3][3] = 1;
*/

	m_matrix[0] =  x * x *(1- cosine) + cosine;
	m_matrix[4] =  x * y * one_minus_cosine - z * sine;
	m_matrix[8] =  x * z * one_minus_cosine + y * sine;

	m_matrix[1] =  x * y * one_minus_cosine + z * sine;
	m_matrix[5] =  y * y * (1.0 - cosine) + cosine;
	m_matrix[9] =  y * z * one_minus_cosine - x * sine;

	m_matrix[2] =  x * z * one_minus_cosine - y * sine;
	m_matrix[6] =  y * z * one_minus_cosine + x * sine;
	m_matrix[10] =  z * z * (1.0 - cosine) + cosine;




	m_matrix[3] = 0;
	m_matrix[7] = 0;
	m_matrix[11] = 0;
	m_matrix[15] = 1;



}

void Matrix::setRotationRadians( const float *angles )
{
	double cr = cos( angles[0] );
	double sr = sin( angles[0] );
	double cp = cos( angles[1] );
	double sp = sin( angles[1] );
	double cy = cos( angles[2] );
	double sy = sin( angles[2] );

	m_matrix[0] = ( float )( cp*cy );
	m_matrix[1] = ( float )( cp*sy );
	m_matrix[2] = ( float )( -sp );

	double srsp = sr*sp;
	double crsp = cr*sp;

	m_matrix[4] = ( float )( srsp*cy-cr*sy );
	m_matrix[5] = ( float )( srsp*sy+cr*cy );
	m_matrix[6] = ( float )( sr*cp );

	m_matrix[8] = ( float )( crsp*cy+sr*sy );
	m_matrix[9] = ( float )( crsp*sy-sr*cy );
	m_matrix[10] = ( float )( cr*cp );
}






void Matrix::setInverseRotationRadians( const float *angles )
{
	double cr = cos( angles[0] );
	double sr = sin( angles[0] );
	double cp = cos( angles[1] );
	double sp = sin( angles[1] );
	double cy = cos( angles[2] );
	double sy = sin( angles[2] );

	m_matrix[0] = ( float )( cp*cy );
	m_matrix[4] = ( float )( cp*sy );
	m_matrix[8] = ( float )( -sp );

	double srsp = sr*sp;
	double crsp = cr*sp;

	m_matrix[1] = ( float )( srsp*cy-cr*sy );
	m_matrix[5] = ( float )( srsp*sy+cr*cy );
	m_matrix[9] = ( float )( sr*cp );

	m_matrix[2] = ( float )( crsp*cy+sr*sy );
	m_matrix[6] = ( float )( crsp*sy-sr*cy );
	m_matrix[10] = ( float )( cr*cp );
}

void Matrix::setRotationQuaternion( const Quaternion& quat )
{
	m_matrix[0] = ( float )( 1.0 - 2.0*quat[1]*quat[1] - 2.0*quat[2]*quat[2] );
	m_matrix[1] = ( float )( 2.0*quat[0]*quat[1] + 2.0*quat[3]*quat[2] );
	m_matrix[2] = ( float )( 2.0*quat[0]*quat[2] - 2.0*quat[3]*quat[1] );

	m_matrix[4] = ( float )( 2.0*quat[0]*quat[1] - 2.0*quat[3]*quat[2] );
	m_matrix[5] = ( float )( 1.0 - 2.0*quat[0]*quat[0] - 2.0*quat[2]*quat[2] );
	m_matrix[6] = ( float )( 2.0*quat[1]*quat[2] + 2.0*quat[3]*quat[0] );

	m_matrix[8] = ( float )( 2.0*quat[0]*quat[2] + 2.0*quat[3]*quat[1] );
	m_matrix[9] = ( float )( 2.0*quat[1]*quat[2] - 2.0*quat[3]*quat[0] );
	m_matrix[10] = ( float )( 1.0 - 2.0*quat[0]*quat[0] - 2.0*quat[1]*quat[1] );
}
