#include "StatisticsWeb.h"
#include <DSConfiguration.h>
#include <DSMySQLQuery.h>
#include <wx/jsonval.h>
#include <wx/jsonwriter.h>
#include "Configuration.h"

StatisticsWeb::StatisticsWeb(
) : DSWeb(
	_N("Content-type: text/html\r\nCache-Control: no-cache\r\n"),
	true,
	DS_WEB_SELFHEADER
) {
}

StatisticsWeb::~StatisticsWeb() {
	if(db.IsConnected())
		db.Disconnect();
}

int StatisticsWeb::Init() {
	DSConfiguration configuration;
	if(configuration.Load(CONFIGURATION_FILE)) {
		templatePath = configuration.Get(_N("TemplatePath")).ToString();
		websiteName = configuration.Get(_N("WebsiteName")).ToString();

		db.SetHostname(configuration.Get(_N("Hostname")).ToString());
		db.SetDatabase(configuration.Get(_N("Database")).ToString());
		db.SetUsername(configuration.Get(_N("Username")).ToString());
		db.SetPassword(configuration.Get(_N("Password")).ToString());
		db.SetPort(configuration.Get(_N("Port")).ToString());

		init = db.Connect();
	}

	return 0;
}

int StatisticsWeb::Run() {
	if(!init) {
		SetStringContent(_N("Could not init"));
	} else {
		const wxString action(GetCgi()->rq[_N("action")]);
		if(action == _N("json"))
			JSON();
		else
			Web();
	}
	
	return 0;
}

DSTemplate StatisticsWeb::CreateTemplate(const wxString &filename) {
	DSTemplate tpl(templatePath);
	tpl.SetFile(filename);
	return tpl;
}

void StatisticsWeb::Web() {
	SetContentType(_N("Content-type: text/html\r\nCache-Control: no-cache\r\n"));

	DSTemplate indexTemplate(CreateTemplate(_N("index.tpl")));

	indexTemplate.SetVariable(_N("websiteName"), websiteName);

	DSTemplate rowsTemplate(CreateTemplate(_N("rows.tpl")));
	DSMySQLQuery query(&db);
	query.Query(_N("SELECT * FROM statistics"));
	while(query.NextRecord()) {
		rowsTemplate.SetVariable(_N("title"), query.GetField(_N("title")).ToString());
		rowsTemplate.SetVariable(_N("counter"), query.GetField(_N("counter")).ToString());
		rowsTemplate.Parse();
	}
	query.FreeResult();

	indexTemplate.SetDynamicVariable(_N("rows"), rowsTemplate.Get());

	indexTemplate.Parse();
	SetStringContent(indexTemplate.Get());
}

void StatisticsWeb::JSON() {
	SetContentType(_N("Content-type: application/json\r\nCache-Control: no-cache\r\n"));
	
	wxJSONValue root;
	root[_N("websiteName")] = websiteName;

	wxJSONValue entry;

	DSMySQLQuery query(&db);
	query.Query(_N("SELECT * FROM statistics"));
	while(query.NextRecord()) {
		entry[_N("title")] = query.GetField(_N("title")).ToString();
		entry[_N("counter")] = query.GetField(_N("counter")).ToString();

		root[_N("entries")].Append(entry);
	}
	query.FreeResult();

	wxJSONWriter writer(wxJSONWRITER_NONE);
	wxString jsonContent;
	writer.Write(root, jsonContent);

	SetStringContent(jsonContent);
}

IMPLEMENT_WEB(StatisticsWeb, statisticsWeb)
