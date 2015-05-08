#include "imageLoader.h"

imageLoader::imageLoader():QObject()
{
  _imaManager = imagesManager::getInstance();   
}

//imageLoader::imageLoader(QString filename)
//{
//  _filename = filename;
//}

void imageLoader::setFilename(QString filename)
{ 
  this->_filename = filename;
}

void imageLoader::readFitsImage(QString fname)
{
  this->_filename = fname;
  try
    {
      if(this->_filename.isNull())
	{  
	  std::string message = "pas de nom de fichier!";
	  throw message;
	}
      cv::Mat *matriceImage;
      std::auto_ptr<CCfits::FITS> pInfile(new CCfits::FITS(_filename.toStdString(),CCfits::Read,true));
      CCfits::PHDU& image = pInfile->pHDU(); 
      
      std::valarray<unsigned long>  contents;
      
      // read all user-specifed, coordinate, and checksum keys in the image
      image.readAllKeys(); 
      //std::cout<<image.bitpix()<<std::endl;
      
      image.read(contents);
      long ax1(image.axis(0));
      long ax2(image.axis(1));
      std::cout<<ax1<<" "<<ax2<<std::endl;
      // create matrix to store image content
      //imageContainer *readImage;
      switch(image.bitpix()) 
	{
	case 8 :
	  matriceImage = new cv::Mat(ax2, ax1, CV_8U);
	  //readImage = new imageContainer(new cv::Mat(ax2, ax1, CV_8U),"loaded8bitImages");
	  break;
	case -32 : // IEEE single precision floating point
	  std::cout<<"Image format:: IEEE single precision floating point"<<std::endl;
	  matriceImage = new cv::Mat(ax2, ax1, CV_32F);
	  // readImage = new imageContainer(new cv::Mat(ax2, ax1, CV_8U),"loaded32bitImages");
	  break;
	case -64 : // IEEE double precision point
	  std::cout<<"Image format:: IEEE double precision floating point"<<std::endl;
	  matriceImage = new cv::Mat(ax2,ax1, CV_64F);
	  //readImage = new imageContainer(new cv::Mat(ax2, ax1, CV_8U),"loaded64bitImages");
	  //imageContainer readImage=imageContainer();
	default :
	  std::string message = "image type not yet implemented";
	  throw message;
      }
      for (int j = 0; j<ax2; ++j)
      {
	for(int k=0; k<ax1 ; ++k)
	  {
	    matriceImage->at<float>(ax2-1-j,k) = contents[k+j*ax1];
	    
	  }
      }
      
      //get the keyword
      std::map< string, CCfits::Keyword * > & filesKeyword=image.keyWord();
      std::map< QString, QString> *headerContent = new std::map< QString, QString>;
      for(std::map<std::string, CCfits::Keyword * >::iterator it=filesKeyword.begin(); it!=filesKeyword.end();++it){
      //std::cout<<  it->first << " => " << *(it->second) << '\n';
      CCfits::Keyword * currentKW = it->second;
      float  v;float  a ;
      //std::cout<<it->second->keytype()<<"--------"<<std::endl;
      if(it->second->keytype()<83 && it->second->keytype()>16)
	a = it->second->value(v);
      
      CCfits::ValueType r=it->second->keytype();
      std::stringstream ss;
      std::complex<float> v14(0,0);
      std::complex<float>  a14(0,0) ;
      std::complex<double> a15(0,0);
      std::complex<double> v15(0,0);
      std::string a4,v4;

      switch(r) 	{
      case CCfits::Tnull  : std::cout << "0\n"; break;
      case CCfits::Tbit : 
	std::cout << "1 \n";
	int  v1;int  a1 ;
	a1 = it->second->value(v1);
	ss << a1;
	break;
      case CCfits::Tbyte : 
	std::cout << "2 \n";
	int  v2;int  a2 ;
	a2 = it->second->value(v2);
	ss << a2;
	break;
      case CCfits::Tlogical : 
	std::cout << "3 \n";
	int  v3;int  a3 ;
	a3 = it->second->value(v3);
	ss << a3;
	break;
      case CCfits::Tstring : 
	std::cout << "4 \n";
	a4 = it->second->value(v4);
	ss << a4;
	break;
      case CCfits::Tushort :
	std::cout << "5 \n";
	int  v5;int  a5 ;
	a5 = it->second->value(v5);
	ss << a5;
	break;
      case CCfits::Tshort :  
	std::cout << "6 \n";
	int  v6;int  a6 ;
	a6 = it->second->value(v6);
	ss << a6;
	break;
      case CCfits::Tuint : 
	std::cout << "7 \n";
	int  v7;int  a7 ;
	a7 = it->second->value(v7);
	ss << a7;
	break;
      case CCfits::Tint :
	std::cout << "8 \n"; 
	int  v8;int  a8 ;
	a8 = it->second->value(v8);
	ss << a8;
	break;
      case CCfits::Tulong :
	std::cout << "9 \n"; 
	int  v9;int  a9 ;
	a9 = it->second->value(v9);
	ss << a9;
	break;
      case CCfits::Tlong : 
	std::cout << "10 \n"; 
	long int  v10;  long int  a10 ;
	a10 = it->second->value(a10);
	ss << a10;
	break;
      case CCfits::Tlonglong : 
	std::cout << "11 \n"; 
	long int  v11;long int  a11 ;
	a11 = it->second->value(a11);
	ss << a11;
	break;
      case CCfits::Tfloat :
	std::cout << "12 \n"; 
	float v12; float a12;
	a12 = it->second->value(v12);
	ss << a12; 
      case CCfits::Tdouble : 
	std::cout << "13 \n";
	float v13; float a13;
	a13 = it->second->value(v13);
	ss << a13;
      case CCfits::Tcomplex : 
	std::cout << "...14 \n"; 
	//a14 = it->second->value(v14);
	//ss << a14.real() <<" + i" << a14.imag();
	break;
      case CCfits::Tdblcomplex : std::cout << "15 \n";break;
	std::cout << "15 \n"; 
	a15 = it->second->value(v15);
	ss << a15.real() <<" + i" << a15.imag();
	break;
	case CCfits::VTbit: std::cout << "16 \n";break;
      case CCfits::VTbyte : std::cout << "17 \n";break;
      case CCfits::VTlogical : std::cout << "18 \n";break;
      case CCfits::VTushort : std::cout << "19 \n";break;
      case CCfits::VTshort : std::cout << "20 \n";break;
      case CCfits::VTuint : std::cout << "21 \n";break;
      case CCfits::VTint: std::cout << "22 \n";break;
      case CCfits::VTulong : std::cout << "23 \n";break;
      case CCfits::VTlong : std::cout << "24 \n";break;
      case CCfits::VTlonglong : std::cout << "25 \n";break;
      case CCfits::VTfloat : std::cout << "26 \n";break;
      case CCfits::VTdouble : std::cout << "27 \n";break;
      case CCfits::VTcomplex : std::cout << "28 \n";break;
      case CCfits::VTdblcomplex : std::cout << "29 \n";break;
      }						 
		
      if(r!=14)
	{
	  std::cout<<(ss.str()).c_str()<<std::endl;
	  headerContent->insert(std::pair<QString,QString>((it->first).c_str(),(ss.str()).c_str()));      
	}
      //std::cout<<"value tentative = " <<ss.str() << std::endl;
      //QTableWidgetItem *currentItem = new QTableWidgetItem();
      //headerTable->setItem(cpt,0,currentItem);
	// currentItem->setText((it->first).c_str());
	//if(r!=14){
	//QTableWidgetItem *currentItem2 = new QTableWidgetItem();
	//headerTable->setItem(cpt,1,currentItem2);
	// currentItem2->setText((ss.str()).c_str());
	//}
	//cpt++;
    } 

      _loadedImage = new imageContainer(matriceImage,"loaded Image");
      _loadedImage->setLoadedOn();
      _loadedImage->setSelectOn();
      _loadedImage->setHeaderContent(headerContent);
      _imaManager->addImageContainerInList(_loadedImage);

 
      emit imageLoadedDone();
    }
  catch(std::string message)
    {
      std::cout<< message << std::endl;
    }
  catch(...)
    {
      std::cout<< "readFits pb !"<<std::endl;
    }
  
}

