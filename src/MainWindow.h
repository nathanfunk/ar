#pragma once

#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

#include "ARMouseHouse.h"
#include "OGLControl.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace ms3dglut {

	/// <summary>
	/// Summary for MainWindow
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class MainWindow : public System::Windows::Forms::Form
	{
	private:
		OGLControl oglControl;
	private: System::Windows::Forms::ToolStripContainer^  toolStripContainer;

	private: System::Windows::Forms::MenuStrip^  menuStrip;

	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  newToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator;
	private: System::Windows::Forms::ToolStripMenuItem^  saveToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  saveAsToolStripMenuItem;



	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator2;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  editToolStripMenuItem;


	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator3;




	private: System::Windows::Forms::ToolStripMenuItem^  selectAllToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  toolsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  customizeToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  optionsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  helpToolStripMenuItem;




	private: System::Windows::Forms::ToolStripMenuItem^  aboutToolStripMenuItem;
	private: System::Windows::Forms::ToolStrip^  standardToolStrip;


	private: System::Windows::Forms::ToolStripButton^  newToolStripButton;
	private: System::Windows::Forms::ToolStripButton^  openToolStripButton;
	private: System::Windows::Forms::ToolStripButton^  saveToolStripButton;






	private: System::Windows::Forms::ToolStripButton^  helpToolStripButton;
	private: System::Windows::Forms::StatusStrip^  statusStrip;
	private: System::Windows::Forms::ToolStripButton^  tsbPartialCylinder;

	private: System::Windows::Forms::ToolStripButton^  tsbFillArc;
	private: System::Windows::Forms::ToolStripButton^  tsbLine;
	private: System::Windows::Forms::ToolStripButton^  tsbPyramid;
	private: System::Windows::Forms::ToolStripButton^  tsbTriangle;
	private: System::Windows::Forms::ToolStripButton^  tsbSphere;
	private: System::Windows::Forms::ToolStrip^  objectsToolStrip;
	private: System::Windows::Forms::ToolStripButton^  tsbCube;
	private: System::Windows::Forms::ToolStripButton^  tsbCone;
	private: System::Windows::Forms::ToolStripButton^  tsbCylinder;
	private: System::Windows::Forms::ToolStripButton^  tsbRectangle;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton5;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton1;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton2;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton3;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton4;
	private: System::Windows::Forms::ToolStrip^  propertiesToolStrip;
	private: System::Windows::Forms::ToolStripButton^  tsbColor;
	private: System::Windows::Forms::ToolStripButton^  tsbTransparency;
	private: System::Windows::Forms::ToolStripButton^  tsbGroup;
	private: System::Windows::Forms::ToolStripButton^  tsbUngroup;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator7;



			 ARMouseHouse *controller;

	public:
		MainWindow(void)
		{
			InitializeComponent();
			controller = new ARMouseHouse(false);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainWindow()
		{
			if (components)
			{
				delete components;
			}

			delete controller;
		}


	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainWindow::typeid));
			this->toolStripContainer = (gcnew System::Windows::Forms::ToolStripContainer());
			this->menuStrip = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->newToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->saveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveAsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->editToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator3 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->selectAllToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->customizeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->optionsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->standardToolStrip = (gcnew System::Windows::Forms::ToolStrip());
			this->newToolStripButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->openToolStripButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->saveToolStripButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->helpToolStripButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->objectsToolStrip = (gcnew System::Windows::Forms::ToolStrip());
			this->tsbTriangle = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsbRectangle = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsbSphere = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsbCube = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsbPyramid = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsbCylinder = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsbCone = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsbFillArc = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsbPartialCylinder = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsbLine = (gcnew System::Windows::Forms::ToolStripButton());
			this->statusStrip = (gcnew System::Windows::Forms::StatusStrip());
			this->propertiesToolStrip = (gcnew System::Windows::Forms::ToolStrip());
			this->tsbColor = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsbTransparency = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsbGroup = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsbUngroup = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripSeparator7 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->toolStripContainer->TopToolStripPanel->SuspendLayout();
			this->toolStripContainer->SuspendLayout();
			this->menuStrip->SuspendLayout();
			this->standardToolStrip->SuspendLayout();
			this->objectsToolStrip->SuspendLayout();
			this->propertiesToolStrip->SuspendLayout();
			this->SuspendLayout();
			// 
			// toolStripContainer
			// 
			// 
			// toolStripContainer.ContentPanel
			// 
			this->toolStripContainer->ContentPanel->Size = System::Drawing::Size(723, 468);
			this->toolStripContainer->Dock = System::Windows::Forms::DockStyle::Fill;
			this->toolStripContainer->Location = System::Drawing::Point(0, 0);
			this->toolStripContainer->Name = L"toolStripContainer";
			this->toolStripContainer->Size = System::Drawing::Size(723, 542);
			this->toolStripContainer->TabIndex = 0;
			this->toolStripContainer->Text = L"toolStripContainer1";
			// 
			// toolStripContainer.TopToolStripPanel
			// 
			this->toolStripContainer->TopToolStripPanel->Controls->Add(this->menuStrip);
			this->toolStripContainer->TopToolStripPanel->Controls->Add(this->standardToolStrip);
			this->toolStripContainer->TopToolStripPanel->Controls->Add(this->objectsToolStrip);
			this->toolStripContainer->TopToolStripPanel->Controls->Add(this->propertiesToolStrip);
			// 
			// menuStrip
			// 
			this->menuStrip->Dock = System::Windows::Forms::DockStyle::None;
			this->menuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->fileToolStripMenuItem, 
				this->editToolStripMenuItem, this->toolsToolStripMenuItem, this->helpToolStripMenuItem});
			this->menuStrip->Location = System::Drawing::Point(0, 0);
			this->menuStrip->Name = L"menuStrip";
			this->menuStrip->Size = System::Drawing::Size(723, 24);
			this->menuStrip->TabIndex = 0;
			this->menuStrip->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {this->newToolStripMenuItem, 
				this->openToolStripMenuItem, this->toolStripSeparator, this->saveToolStripMenuItem, this->saveAsToolStripMenuItem, this->toolStripSeparator2, 
				this->exitToolStripMenuItem});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(35, 20);
			this->fileToolStripMenuItem->Text = L"&File";
			// 
			// newToolStripMenuItem
			// 
			this->newToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"newToolStripMenuItem.Image")));
			this->newToolStripMenuItem->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->newToolStripMenuItem->Name = L"newToolStripMenuItem";
			this->newToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::N));
			this->newToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->newToolStripMenuItem->Text = L"&New";
			// 
			// openToolStripMenuItem
			// 
			this->openToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"openToolStripMenuItem.Image")));
			this->openToolStripMenuItem->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			this->openToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::O));
			this->openToolStripMenuItem->Size = System::Drawing::Size(140, 22);
			this->openToolStripMenuItem->Text = L"&Open";
			// 
			// toolStripSeparator
			// 
			this->toolStripSeparator->Name = L"toolStripSeparator";
			this->toolStripSeparator->Size = System::Drawing::Size(137, 6);
			// 
			// saveToolStripMenuItem
			// 
			this->saveToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"saveToolStripMenuItem.Image")));
			this->saveToolStripMenuItem->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->saveToolStripMenuItem->Name = L"saveToolStripMenuItem";
			this->saveToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::S));
			this->saveToolStripMenuItem->Size = System::Drawing::Size(140, 22);
			this->saveToolStripMenuItem->Text = L"&Save";
			// 
			// saveAsToolStripMenuItem
			// 
			this->saveAsToolStripMenuItem->Name = L"saveAsToolStripMenuItem";
			this->saveAsToolStripMenuItem->Size = System::Drawing::Size(140, 22);
			this->saveAsToolStripMenuItem->Text = L"Save &As";
			// 
			// toolStripSeparator2
			// 
			this->toolStripSeparator2->Name = L"toolStripSeparator2";
			this->toolStripSeparator2->Size = System::Drawing::Size(137, 6);
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(140, 22);
			this->exitToolStripMenuItem->Text = L"E&xit";
			// 
			// editToolStripMenuItem
			// 
			this->editToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->toolStripSeparator3, 
				this->selectAllToolStripMenuItem});
			this->editToolStripMenuItem->Name = L"editToolStripMenuItem";
			this->editToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->editToolStripMenuItem->Text = L"&Edit";
			// 
			// toolStripSeparator3
			// 
			this->toolStripSeparator3->Name = L"toolStripSeparator3";
			this->toolStripSeparator3->Size = System::Drawing::Size(136, 6);
			// 
			// selectAllToolStripMenuItem
			// 
			this->selectAllToolStripMenuItem->Name = L"selectAllToolStripMenuItem";
			this->selectAllToolStripMenuItem->Size = System::Drawing::Size(139, 22);
			this->selectAllToolStripMenuItem->Text = L"Select &All";
			// 
			// toolsToolStripMenuItem
			// 
			this->toolsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->customizeToolStripMenuItem, 
				this->optionsToolStripMenuItem});
			this->toolsToolStripMenuItem->Name = L"toolsToolStripMenuItem";
			this->toolsToolStripMenuItem->Size = System::Drawing::Size(44, 20);
			this->toolsToolStripMenuItem->Text = L"&Tools";
			// 
			// customizeToolStripMenuItem
			// 
			this->customizeToolStripMenuItem->Name = L"customizeToolStripMenuItem";
			this->customizeToolStripMenuItem->Size = System::Drawing::Size(123, 22);
			this->customizeToolStripMenuItem->Text = L"&Customize";
			// 
			// optionsToolStripMenuItem
			// 
			this->optionsToolStripMenuItem->Name = L"optionsToolStripMenuItem";
			this->optionsToolStripMenuItem->Size = System::Drawing::Size(123, 22);
			this->optionsToolStripMenuItem->Text = L"&Options";
			// 
			// helpToolStripMenuItem
			// 
			this->helpToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->aboutToolStripMenuItem});
			this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
			this->helpToolStripMenuItem->Size = System::Drawing::Size(40, 20);
			this->helpToolStripMenuItem->Text = L"&Help";
			// 
			// aboutToolStripMenuItem
			// 
			this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
			this->aboutToolStripMenuItem->Size = System::Drawing::Size(118, 22);
			this->aboutToolStripMenuItem->Text = L"&About...";
			// 
			// standardToolStrip
			// 
			this->standardToolStrip->Dock = System::Windows::Forms::DockStyle::None;
			this->standardToolStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {this->newToolStripButton, 
				this->openToolStripButton, this->saveToolStripButton, this->toolStripSeparator7, this->helpToolStripButton});
			this->standardToolStrip->Location = System::Drawing::Point(3, 24);
			this->standardToolStrip->Name = L"standardToolStrip";
			this->standardToolStrip->Size = System::Drawing::Size(110, 25);
			this->standardToolStrip->TabIndex = 0;
			this->standardToolStrip->Text = L"toolStrip1";
			// 
			// newToolStripButton
			// 
			this->newToolStripButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->newToolStripButton->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"newToolStripButton.Image")));
			this->newToolStripButton->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->newToolStripButton->Name = L"newToolStripButton";
			this->newToolStripButton->Size = System::Drawing::Size(23, 22);
			this->newToolStripButton->Text = L"&New";
			// 
			// openToolStripButton
			// 
			this->openToolStripButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->openToolStripButton->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"openToolStripButton.Image")));
			this->openToolStripButton->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->openToolStripButton->Name = L"openToolStripButton";
			this->openToolStripButton->Size = System::Drawing::Size(23, 22);
			this->openToolStripButton->Text = L"&Open";
			// 
			// saveToolStripButton
			// 
			this->saveToolStripButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->saveToolStripButton->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"saveToolStripButton.Image")));
			this->saveToolStripButton->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->saveToolStripButton->Name = L"saveToolStripButton";
			this->saveToolStripButton->Size = System::Drawing::Size(23, 22);
			this->saveToolStripButton->Text = L"&Save";
			// 
			// helpToolStripButton
			// 
			this->helpToolStripButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->helpToolStripButton->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"helpToolStripButton.Image")));
			this->helpToolStripButton->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->helpToolStripButton->Name = L"helpToolStripButton";
			this->helpToolStripButton->Size = System::Drawing::Size(23, 22);
			this->helpToolStripButton->Text = L"He&lp";
			// 
			// objectsToolStrip
			// 
			this->objectsToolStrip->Dock = System::Windows::Forms::DockStyle::None;
			this->objectsToolStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(10) {this->tsbTriangle, 
				this->tsbRectangle, this->tsbSphere, this->tsbCube, this->tsbPyramid, this->tsbCylinder, this->tsbCone, this->tsbFillArc, this->tsbPartialCylinder, 
				this->tsbLine});
			this->objectsToolStrip->Location = System::Drawing::Point(3, 49);
			this->objectsToolStrip->Name = L"objectsToolStrip";
			this->objectsToolStrip->Size = System::Drawing::Size(488, 25);
			this->objectsToolStrip->TabIndex = 1;
			this->objectsToolStrip->Text = L"Objects";
			// 
			// tsbTriangle
			// 
			this->tsbTriangle->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->tsbTriangle->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsbTriangle.Image")));
			this->tsbTriangle->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsbTriangle->Name = L"tsbTriangle";
			this->tsbTriangle->Size = System::Drawing::Size(49, 22);
			this->tsbTriangle->Text = L"Triangle";
			this->tsbTriangle->Click += gcnew System::EventHandler(this, &MainWindow::ObjectsToolStrip_Click);
			// 
			// tsbRectangle
			// 
			this->tsbRectangle->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->tsbRectangle->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsbRectangle.Image")));
			this->tsbRectangle->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsbRectangle->Name = L"tsbRectangle";
			this->tsbRectangle->Size = System::Drawing::Size(59, 22);
			this->tsbRectangle->Text = L"Rectangle";
			this->tsbRectangle->Click += gcnew System::EventHandler(this, &MainWindow::ObjectsToolStrip_Click);
			// 
			// tsbSphere
			// 
			this->tsbSphere->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->tsbSphere->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsbSphere.Image")));
			this->tsbSphere->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsbSphere->Name = L"tsbSphere";
			this->tsbSphere->Size = System::Drawing::Size(45, 22);
			this->tsbSphere->Text = L"Sphere";
			this->tsbSphere->Click += gcnew System::EventHandler(this, &MainWindow::ObjectsToolStrip_Click);
			// 
			// tsbCube
			// 
			this->tsbCube->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->tsbCube->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsbCube.Image")));
			this->tsbCube->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsbCube->Name = L"tsbCube";
			this->tsbCube->Size = System::Drawing::Size(36, 22);
			this->tsbCube->Text = L"Cube";
			this->tsbCube->Click += gcnew System::EventHandler(this, &MainWindow::ObjectsToolStrip_Click);
			// 
			// tsbPyramid
			// 
			this->tsbPyramid->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->tsbPyramid->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsbPyramid.Image")));
			this->tsbPyramid->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsbPyramid->Name = L"tsbPyramid";
			this->tsbPyramid->Size = System::Drawing::Size(49, 22);
			this->tsbPyramid->Text = L"Pyramid";
			this->tsbPyramid->Click += gcnew System::EventHandler(this, &MainWindow::ObjectsToolStrip_Click);
			// 
			// tsbCylinder
			// 
			this->tsbCylinder->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->tsbCylinder->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsbCylinder.Image")));
			this->tsbCylinder->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsbCylinder->Name = L"tsbCylinder";
			this->tsbCylinder->Size = System::Drawing::Size(50, 22);
			this->tsbCylinder->Text = L"Cylinder";
			this->tsbCylinder->Click += gcnew System::EventHandler(this, &MainWindow::ObjectsToolStrip_Click);
			// 
			// tsbCone
			// 
			this->tsbCone->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->tsbCone->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsbCone.Image")));
			this->tsbCone->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsbCone->Name = L"tsbCone";
			this->tsbCone->Size = System::Drawing::Size(36, 22);
			this->tsbCone->Text = L"Cone";
			this->tsbCone->Click += gcnew System::EventHandler(this, &MainWindow::ObjectsToolStrip_Click);
			// 
			// tsbFillArc
			// 
			this->tsbFillArc->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->tsbFillArc->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsbFillArc.Image")));
			this->tsbFillArc->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsbFillArc->Name = L"tsbFillArc";
			this->tsbFillArc->Size = System::Drawing::Size(39, 22);
			this->tsbFillArc->Text = L"FillArc";
			this->tsbFillArc->Click += gcnew System::EventHandler(this, &MainWindow::ObjectsToolStrip_Click);
			// 
			// tsbPartialCylinder
			// 
			this->tsbPartialCylinder->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->tsbPartialCylinder->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsbPartialCylinder.Image")));
			this->tsbPartialCylinder->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsbPartialCylinder->Name = L"tsbPartialCylinder";
			this->tsbPartialCylinder->Size = System::Drawing::Size(83, 22);
			this->tsbPartialCylinder->Text = L"Partial Cylinder";
			this->tsbPartialCylinder->Click += gcnew System::EventHandler(this, &MainWindow::ObjectsToolStrip_Click);
			// 
			// tsbLine
			// 
			this->tsbLine->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->tsbLine->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsbLine.Image")));
			this->tsbLine->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsbLine->Name = L"tsbLine";
			this->tsbLine->Size = System::Drawing::Size(30, 22);
			this->tsbLine->Text = L"Line";
			this->tsbLine->Click += gcnew System::EventHandler(this, &MainWindow::ObjectsToolStrip_Click);
			// 
			// statusStrip
			// 
			this->statusStrip->Location = System::Drawing::Point(0, 520);
			this->statusStrip->Name = L"statusStrip";
			this->statusStrip->Size = System::Drawing::Size(723, 22);
			this->statusStrip->TabIndex = 1;
			this->statusStrip->Text = L"statusStrip";
			// 
			// propertiesToolStrip
			// 
			this->propertiesToolStrip->Dock = System::Windows::Forms::DockStyle::None;
			this->propertiesToolStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->tsbColor, 
				this->tsbTransparency, this->tsbGroup, this->tsbUngroup});
			this->propertiesToolStrip->Location = System::Drawing::Point(114, 24);
			this->propertiesToolStrip->Name = L"propertiesToolStrip";
			this->propertiesToolStrip->Size = System::Drawing::Size(248, 25);
			this->propertiesToolStrip->TabIndex = 2;
			// 
			// tsbColor
			// 
			this->tsbColor->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->tsbColor->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsbColor.Image")));
			this->tsbColor->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsbColor->Name = L"tsbColor";
			this->tsbColor->Size = System::Drawing::Size(36, 22);
			this->tsbColor->Text = L"Color";
			this->tsbColor->Click += gcnew System::EventHandler(this, &MainWindow::tsbColor_Click);
			// 
			// tsbTransparency
			// 
			this->tsbTransparency->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->tsbTransparency->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsbTransparency.Image")));
			this->tsbTransparency->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsbTransparency->Name = L"tsbTransparency";
			this->tsbTransparency->Size = System::Drawing::Size(77, 22);
			this->tsbTransparency->Text = L"Transparency";
			// 
			// tsbGroup
			// 
			this->tsbGroup->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->tsbGroup->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsbGroup.Image")));
			this->tsbGroup->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsbGroup->Name = L"tsbGroup";
			this->tsbGroup->Size = System::Drawing::Size(40, 22);
			this->tsbGroup->Text = L"Group";
			// 
			// tsbUngroup
			// 
			this->tsbUngroup->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->tsbUngroup->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsbUngroup.Image")));
			this->tsbUngroup->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsbUngroup->Name = L"tsbUngroup";
			this->tsbUngroup->Size = System::Drawing::Size(52, 22);
			this->tsbUngroup->Text = L"Ungroup";
			// 
			// toolStripSeparator7
			// 
			this->toolStripSeparator7->Name = L"toolStripSeparator7";
			this->toolStripSeparator7->Size = System::Drawing::Size(6, 25);
			// 
			// MainWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(723, 542);
			this->Controls->Add(this->statusStrip);
			this->Controls->Add(this->toolStripContainer);
			this->Name = L"MainWindow";
			this->Text = L"MainWindow";
			this->Load += gcnew System::EventHandler(this, &MainWindow::MainWindow_Load);
			this->toolStripContainer->TopToolStripPanel->ResumeLayout(false);
			this->toolStripContainer->TopToolStripPanel->PerformLayout();
			this->toolStripContainer->ResumeLayout(false);
			this->toolStripContainer->PerformLayout();
			this->menuStrip->ResumeLayout(false);
			this->menuStrip->PerformLayout();
			this->standardToolStrip->ResumeLayout(false);
			this->standardToolStrip->PerformLayout();
			this->objectsToolStrip->ResumeLayout(false);
			this->objectsToolStrip->PerformLayout();
			this->propertiesToolStrip->ResumeLayout(false);
			this->propertiesToolStrip->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private:
	System::Void MainWindow_Load(System::Object^  sender, System::EventArgs^  e) {
		// Add the openGL control to the content panel of the toolstrip container
		this->toolStripContainer->ContentPanel->Controls->Add(%oglControl);
		oglControl.Name = L"OpenGL Control";	// give some name
		oglControl.Dock = DockStyle::Fill;		// set to fill contentpanel

		// Initialize controller and hook together OpenGL control to the controller
		controller->InitGL();
		controller->ar_init();
		oglControl.setController(controller);

		// Start video capture now that everything's set up
		arVideoCapStart();
	}

	System::Void ObjectsToolStrip_Click(System::Object^ sender, System::EventArgs^ e) {
		System::String ^name = ((ToolStripItem^)sender)->Name;

		if (name == "tsbCone" ) {
			controller->addObject(ObjectTypes::CONE);
		} else if (name == "tsbCube" ) {
			controller->addObject(ObjectTypes::CUBE);
		} else if (name == "tsbCylinder" ) {
			controller->addObject(ObjectTypes::CYLINDER);
		} else if (name == "tsbFillArc" ) {
			controller->addObject(ObjectTypes::FILLARC);
		} else if (name == "tsbLine" ) {
			controller->addObject(ObjectTypes::LINE);
		} else if (name == "tsbPartialCylinder" ) {
			controller->addObject(ObjectTypes::PARTIALCYLINDER);
		} else if (name == "tsbPyramid" ) {
			controller->addObject(ObjectTypes::PYRAMID);
		} else if (name == "tsbRectangle" ) {
			controller->addObject(ObjectTypes::RECTANGLE);
		} else if (name == "tsbSphere" ) {
			controller->addObject(ObjectTypes::SPHERE);
		} else if (name == "tsbTriangle" ) {
			controller->addObject(ObjectTypes::TRIANGLE);
		}
	}

	System::Void tsbColor_Click(System::Object^  sender, System::EventArgs^  e) {
		ColorDialog cd;
		// show color dialog
		cd.ShowDialog(this);

		// get selected color and change object
		controller->setColors(cd.Color.R/255.0, cd.Color.G/255.0, cd.Color.B/255.0);
	}
};
}
