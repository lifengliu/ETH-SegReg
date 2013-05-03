#include "Log.h"

#include <stdio.h>
#include <iostream>
#include "argstream.h"
#include "ImageUtils.h"
#include <itkWarpImageFilter.h>

#include "TransformationUtils.h"


using namespace std;
using namespace itk;




int main(int argc, char ** argv)
{
    LOG<<CLOCKS_PER_SEC<<endl;

	feenableexcept(FE_INVALID|FE_DIVBYZERO|FE_OVERFLOW);
    typedef unsigned char PixelType;
    const unsigned int D=2;
    typedef Image<PixelType,D> ImageType;
    typedef ImageType::Pointer ImagePointerType;
    typedef ImageType::ConstPointer ImageConstPointerType;
    typedef Vector<float,D> LabelType;
    typedef Image<LabelType,D> LabelImageType;
    typedef LabelImageType::Pointer LabelImagePointerType;
    typedef ImageType::IndexType IndexType;
    
    LabelImagePointerType deformation1 = ImageUtils<LabelImageType>::readImage(argv[1]);

    LabelImagePointerType deformation2 = ImageUtils<LabelImageType>::readImage(argv[2]);
    
    LabelImagePointerType composedDeformation= TransfUtils<ImageType>::composeDeformations(deformation2,deformation1) ;
    
    if (argc > 4){
        LabelImagePointerType deformation3= ImageUtils<LabelImageType>::readImage(argv[3]);
        composedDeformation=TransfUtils<ImageType>::composeDeformations(deformation3,composedDeformation) ;
        ImageUtils<LabelImageType>::writeImage(argv[4],composedDeformation);

    }else
        {
        ImageUtils<LabelImageType>::writeImage(argv[3],composedDeformation);
    }
    LOG<<"deformed image "<<argv[1]<<endl;
	return 1;
}
