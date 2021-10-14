#include "mosaic.hpp"

/***********************************************************************************************************************************
* Define the initial state of the MosaicManager singleton instance
***********************************************************************************************************************************/
Mosaic* Mosaic::instance = NULL;


/***********************************************************************************************************************************
*
*
***********************************************************************************************************************************/
Mosaic *Mosaic::getInstance() {
	return Mosaic::instance;
}

