#ifndef ODESFEPEDESTALINFO_H
#define ODESFEPEDESTALINFO_H

#include <map>
#include <string>

#include "OnlineDB/EcalCondDB/interface/Tm.h"
#include "OnlineDB/EcalCondDB/interface/DateHandler.h"
#include "OnlineDB/EcalCondDB/interface/IDataItem.h"
#include "OnlineDB/EcalCondDB/interface/EcalLogicID.h"
#include "OnlineDB/EcalCondDB/interface/IODConfig.h"


class ODESFEPedestalOffsetInfo : public IODConfig {
 public:
  friend class EcalCondDBInterface;

  ODESFEPedestalOffsetInfo();
  ~ODESFEPedestalOffsetInfo();


  // User data methods
  inline std::string getTable() { return "ES_FE_CONF_INFO"; }

  inline void setId(int id) { m_ID = id; }
  inline int getId() const { return m_ID; }

  // the tag is already in IODConfig 

  inline void setVersion(int id) { m_version = id; }
  inline int getVersion() const { return m_version; }
  
  inline void setIov_pl(int iov) { m_iov_id_pl = iov; }
  inline int getIov_pl() const { return m_iov_id_pl; }
  
  inline void setIov_mi(int iov) { m_iov_id_mi = iov; }
  inline int getIov_mi() const { return m_iov_id_mi; }
  
  inline void setUser_comment(std::string comment) { m_user_comment = comment; }
  inline std::string getUser_comment() const { return m_user_comment; }

  inline void setRunIov_P(int run) {m_iov_P = run;}
  inline void setRunIov_M(int run) {m_iov_M = run;}
  inline int getRunIov_P() const { return m_iov_P; }
  inline int getRunIov_M() const { return m_iov_M; }

  inline void setMagnet(int id) { m_magnet = id; }
  inline int getMagnet() const { return m_magnet; }
  inline void setGain(int id) { m_gain = id; }
  inline int getGain() const { return m_gain; }
  inline void setZero(int id) { m_zero = id; }
  inline int getZero() const { return m_zero; }


  int fetchNextId() throw(std::runtime_error);
  void setParameters(const std::map<std::string,std::string>& my_keys_map);

  int fetchID()  throw(std::runtime_error);

  std::map< int,int > fetchGain(const std::string gain)  throw(std::runtime_error);
  std::map< int,int > fetchIovId(const int runp, const int runm)  throw(std::runtime_error);
 
private:
  void prepareWrite()  throw(std::runtime_error);
  void fetchLastData(ODESFEPedestalOffsetInfo * result)     throw(std::runtime_error);
  void writeDB()       throw(std::runtime_error);

  void clear();

  void fetchData(ODESFEPedestalOffsetInfo * result)     throw(std::runtime_error);
 

  // User data
  int m_ID;
  std::string m_Tag;
  int m_version;
  int m_iov_id_pl;
  int m_iov_id_mi;
  std::string m_user_comment;
  int m_iov_P;
  int m_iov_M;
  int m_magnet;
  int m_gain;
  int m_zero;

};

#endif
