#ifndef STATISTICS_WEB_H_
#define STATISTICS_WEB_H_

#include <DSWeb.h>
#include <DSTemplate.h>
#include <DSMySQLDatabase.h>

using namespace DynSoft;

class StatisticsWeb : public DSWeb {

	public:
		StatisticsWeb();
		~StatisticsWeb();

		int Init();
		int Run();
	
	private:
		bool init = false;
		wxString templatePath;
		wxString websiteName;
		DSMySQLDatabase db;
		
		DSTemplate CreateTemplate(const wxString &filename);
		void Web();
		void JSON();



};

#endif /* STATISTICS_WEB_H_ */
