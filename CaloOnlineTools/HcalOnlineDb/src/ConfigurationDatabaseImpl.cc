#include "CaloOnlineTools/HcalOnlineDb/interface/ConfigurationDatabaseImpl.hh"

namespace hcal {

ConfigurationDatabaseImpl::ConfigurationDatabaseImpl() : m_logger(log4cplus::Logger::getInstance("hcal_ConfigurationDatabaseImpl")) {
  }

  void ConfigurationDatabaseImpl::parseAccessor(const std::string& accessor, std::string& method, std::string& host, std::string& port, std::string& user, std::string& db, std::map<std::string,std::string>& params) {
    std::string::size_type start,end;

    method.clear(); host.clear(); port.clear(); user.clear(); db.clear(); params.clear();

    if (accessor.empty()) return;

    // method    
    start=0;
    end=accessor.find("://");
    if (end==std::string::npos) return;

    method=accessor.substr(start,end-start);
    start=end+3; // skip past :// 

    end=accessor.find('@',start); // user?
    if (end!=std::string::npos) {
      user=accessor.substr(start,end-start);
      start=end+1;
    }
    
    end=accessor.find(':',start); // port?
    if (end!=std::string::npos) {
      host=accessor.substr(start,end-start); // host is here, port is next
      start=end+1;
    } 
    
    end=accessor.find('/',start); // port or host
    if (end==std::string::npos) return; // problems...
    if (host.empty()) host=accessor.substr(start,end-start);
    else port=accessor.substr(start,end-start);
    start=end+1;

    end=accessor.find('?',start); // database
    if (end==std::string::npos) {
      db=accessor.substr(start);
      return;
    } else db=accessor.substr(start,end-start);
    start=end; //  beginning of the parameters
    
    // parameters
    std::string pname,pvalue;
    while (start!=std::string::npos) {
      start+=1;
      end=accessor.find('=',start);
      if (end==std::string::npos) break; // no equals
      pname=accessor.substr(start,end-start);
      start=end+1;
      end=accessor.find_first_of(",&",start);
      if (end==std::string::npos) {
	pvalue=accessor.substr(start);
      } else {
	pvalue=accessor.substr(start,end-start);
      }
      params[pname]=pvalue;
      start=end;
    }
  }

  std::vector<std::string> ConfigurationDatabaseImpl::getValidTags() throw (hcal::exception::ConfigurationDatabaseException) {
    XCEPT_RAISE(hcal::exception::ConfigurationDatabaseException,"Not implemented");
  }
  ConfigurationDatabase::ApplicationConfig ConfigurationDatabaseImpl::getApplicationConfig(const std::string& tag, const std::string& classname, int instance) throw (hcal::exception::ConfigurationDatabaseException) {
    XCEPT_RAISE(hcal::exception::ConfigurationDatabaseException,"Not implemented");
  }

  std::string ConfigurationDatabaseImpl::getConfigurationDocument(const std::string& tag) throw (hcal::exception::ConfigurationDatabaseException) {
    XCEPT_RAISE(hcal::exception::ConfigurationDatabaseException,"Not implemented");
  }

  unsigned int ConfigurationDatabaseImpl::getFirmwareChecksum(const std::string& board, unsigned int version) throw (hcal::exception::ConfigurationDatabaseException) {
    XCEPT_RAISE(hcal::exception::ConfigurationDatabaseException,"Not implemented");
  }
  
  void ConfigurationDatabaseImpl::getFirmwareMCS(const std::string& board, unsigned int version, std::vector<std::string>& mcsLines) throw (hcal::exception::ConfigurationDatabaseException) {
    XCEPT_RAISE(hcal::exception::ConfigurationDatabaseException,"Not implemented");
  }
  void ConfigurationDatabaseImpl::getLUTs(const std::string& tag,int crate, int slot, std::map<ConfigurationDatabase::LUTId, ConfigurationDatabase::LUT >& LUTs) throw (hcal::exception::ConfigurationDatabaseException) {
    XCEPT_RAISE(hcal::exception::ConfigurationDatabaseException,"Not implemented");
  }
  void ConfigurationDatabaseImpl::getLUTChecksums(const std::string& tag, std::map<ConfigurationDatabase::LUTId, ConfigurationDatabase::MD5Fingerprint>& checksums) throw (hcal::exception::ConfigurationDatabaseException) {
    XCEPT_RAISE(hcal::exception::ConfigurationDatabaseException,"Not implemented");
  }
  void ConfigurationDatabaseImpl::getPatterns(const std::string& tag, int crate, int slot, std::map<ConfigurationDatabase::PatternId, ConfigurationDatabase::HTRPattern>& patterns) throw (hcal::exception::ConfigurationDatabaseException) {
    XCEPT_RAISE(hcal::exception::ConfigurationDatabaseException,"Not implemented");
  }
  void ConfigurationDatabaseImpl::getZSThresholds(const std::string& tag, int crate, int slot, std::map<ConfigurationDatabase::ZSChannelId, int>& thresholds) throw (hcal::exception::ConfigurationDatabaseException) {
    XCEPT_RAISE(hcal::exception::ConfigurationDatabaseException,"Not implemented");
  }
  void ConfigurationDatabaseImpl::getHLXMasks(const std::string& tag, int crate, int slot, std::map<ConfigurationDatabase::FPGAId, ConfigurationDatabase::HLXMasks>& masks) throw (hcal::exception::ConfigurationDatabaseException) {
    XCEPT_RAISE(hcal::exception::ConfigurationDatabaseException,"Not implemented");
  }
  void ConfigurationDatabaseImpl::getRBXdata(const std::string& tag,
					     const std::string& rbx,
					     ConfigurationDatabase::RBXdatumType dtype,
					     std::map<ConfigurationDatabase::RBXdatumId, ConfigurationDatabase::RBXdatum>& RBXdata) 
    throw (hcal::exception::ConfigurationDatabaseException) {
    XCEPT_RAISE(hcal::exception::ConfigurationDatabaseException,"Not implemented");
  }
  void ConfigurationDatabaseImpl::getRBXpatterns(const std::string& tag,
						 const std::string& rbx,
						 std::map<ConfigurationDatabase::RBXdatumId, ConfigurationDatabase::RBXpattern>& patterns)
    throw (hcal::exception::ConfigurationDatabaseException) {
    XCEPT_RAISE(hcal::exception::ConfigurationDatabaseException,"Not implemented");
  }

  // added by Gena Kukartsev
  oracle::occi::Connection * ConfigurationDatabaseImpl::getConnection( void ){
    return NULL;
  }
  
  oracle::occi::Environment * ConfigurationDatabaseImpl::getEnvironment( void ){
    return NULL;
  }

}
