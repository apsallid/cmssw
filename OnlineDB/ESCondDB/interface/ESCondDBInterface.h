/***********************************************/
/* ESCondDBInterface.h		       */
/* 					       */
/* $Id: ESCondDBInterface.h,v 1.2 2010/02/17 10:11:17 gcheveni Exp $ 	        		       */
/* 					       */
/* Interface to the ES Conditions DB.	       */
/***********************************************/

#ifndef ESCONDDBINTERFACE_HH
#define ESCONDDBINTERFACE_HH

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include "OnlineDB/Oracle/interface/Oracle.h"

#include "OnlineDB/ESCondDB/interface/ESCondDBInterface.h"
#include "OnlineDB/EcalCondDB/interface/EcalDBConnection.h"
#include "OnlineDB/EcalCondDB/interface/EcalCondDBInterface.h"
#include "OnlineDB/EcalCondDB/interface/Tm.h"
#include "OnlineDB/EcalCondDB/interface/EcalLogicID.h"
#include "OnlineDB/EcalCondDB/interface/IIOV.h"
#include "OnlineDB/EcalCondDB/interface/RunIOV.h"

#include "OnlineDB/ESCondDB/interface/ESMonRunIOV.h"


class ESCondDBInterface : public EcalCondDBInterface {
 friend class EcalCondDBInterface;

 public:

 /**
  *  Constructor, makes connection to DB without TNS_ADMIN
  *  === Parameters ===
  *  host:    DB host machine
  *  sid:     DB SID (name)
  *  user:    User to connect
  *  pass:    Password for user
  *  port:    port number to connect, default 1521
  */
 ESCondDBInterface( std::string host,
		      std::string sid,
		      std::string user,
		      std::string pass,
		    int port=10121 ) //was 1521
   : EcalCondDBInterface ( host, sid, user, pass, port )
   {
     // call the parent constructor

     // create a DateHandler
   //  dh = new DateHandler(env, conn);
   }



 /**
  *  Constructor, makes connection to DB with TNS_ADMIN
  *  === Parameters ===
  *  sid:     DB SID (name)
  *  user:    User to connect
  *  pass:    Password for user
  */
 ESCondDBInterface( std::string sid,
		      std::string user,
		      std::string pass )
   : EcalCondDBInterface( sid, user, pass )
   {
     // call the parent constructor

     // create a DateHandler
   //  dh = new DateHandler(env, conn);
   }


 /**
  * Destructor
  */
 virtual ~ESCondDBInterface()
   throw(std::runtime_error)
   {
     // call the parent destructor

     // destroy the DateHandler
    // delete(dh);
   }



  /**
   *  Return a ES monitoring run object
   */
 ESMonRunIOV fetchESMonRunIOV(RunTag* runtag, std::string montag, run_t run, subrun_t monrun)
    throw(std::runtime_error);


 std::string query_location(const int num) throw(std::runtime_error);

 int query_side(const int num) throw(std::runtime_error);


  /*
   *  Fetch a set of data based on an EXACT match of an iov
   */

 /*
  template<class DATT, class ICONF>
  void fetchConfigDataSetFromCondDB(std::vector< DATT >* fillMap, ICONF* iconf)
    throw(std::runtime_error)
  {

    DATT datiface;
    datiface.setConnection(env, conn);
    datiface.createReadStatement();
    datiface.setPrefetchRowCount(1024);
    datiface.fetchDataFromCondDB( fillMap, iconf );
    datiface.terminateReadStatement();

  }


 */




 private:

  /*********************\
  -  private variables  -
  \*********************/



};

#endif
