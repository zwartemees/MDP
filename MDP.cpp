//
// Created by zwartemees on 07/11/2024.
// last edit on 23/04/2024
//

#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>
#include <regex>
#include <string.h>
#include "mongoose.h"

using namespace std;

int listDepth = 0;
string currentVersion = "0.0.1";
string help = "to reopen this menu use parameter -h/ --help\nto present run MDP <path-to-file>\n other supported arguments:\n -v/ --version\n\t to show the version number\n-t/ --tab followed by the number of spaces one tab is.\nThe standard is 4.\n-r/ --references\n To show a reference page at the end of the slide show. otherwise the refrences will show when a link is clicked but not when presenting";
string path = "";
string refrences = "";
int spacesForOneTab = 4;
bool showRef = false;
int quoteRef = 0;
int extraDivsToClose = 0;



enum currentHtmlElement {
	ORDEREDLIST,
	UNORDERDLIST,
	TABLE,
	CODEBLOCK,
	QUOTE,
	TASKLIST,
	COMMENT,
	NOTINUSE
};

string getCodeblock(string input, currentHtmlElement& elementType) {
	if (regex_search(input, regex("```"))) {
		if (elementType == NOTINUSE) {
			elementType = CODEBLOCK;
			return "<pre><code class = \"language-" + input.substr(3) + "\">\n";

		}
		else
		{
			elementType = NOTINUSE;
			return "</code></pre>";
		}
	}
	return input + "\n";
}

string getQuote(vector<string>& elements, int& i, currentHtmlElement& elementType) {
	string output = "";
	if (regex_search(elements[i], regex("> \\[!.*\\]"))) {
		elementType = QUOTE;
		
		smatch match1;
		regex_search(elements[i], match1, regex("\\[!.*\\]"));
		string altText = match1.str(0).substr(2, match1.str(0).length() - 3);
		
		output += "<blockquote class=\"" + altText +"\">\n";
		
		smatch match2;
		if (regex_search(elements[i], match2, regex("\\(.*\\)"))) {
			string link = match2.str(0).substr(1, match2.str(0).length() - 2);
			quoteRef += 1;
			output += "< a href = \"" +link+ "\">" + to_string(quoteRef) + "</a>\n";

		}
	}
	else if(elementType != QUOTE){
		output += "<blockquote> \n";
		output += elements[i].substr(2) + "\n";
		elementType = QUOTE;
	}
	else {
		output += elements[i].substr(2) + "\n";
	}
	if (!(regex_search(elements[i+1], regex("> ")))) {
		elementType = NOTINUSE;
		output += "</blockquote>\n";
	}
	return output;		
}
string getStartOfOrderedList(string input) {
	smatch match;
	if (regex_search(input, regex("^ *[0-9]+|^\t*[0-9]+")))
	{
		regex_search(input, match, regex("[0-9]+"));
		
		return "<ol start = \"" + match.str(0) + "\">\n";
	}
	return "<ol>\n";
}

string makeOrderedList(const regex& reg, vector<string>& elements, int& i, int  depth, currentHtmlElement& elementType) {
	
	string output = "";

	if (elementType != ORDEREDLIST) {
		elementType = ORDEREDLIST;
		output +=  getStartOfOrderedList(elements[i]);

	}
	if (depth > listDepth) {
		output += getStartOfOrderedList(elements[i]);
		listDepth++;
	}
	output += "<li> " + regex_replace(elements[i], reg, " ") + "</li>\n";

	if ((!regex_search(elements[i + 1], reg) && listDepth > 0)) {
		output += "</ol>\n";
		listDepth--;
	}
	else if (!regex_search(elements[i + 1], regex("^\t*[0-9]+\\. |^ *[0-9]+\\. |^\t*[a-z]\\. |^ *[a-z]\\. "))) {
		output += "</ol>\n";
		elementType = NOTINUSE;
	}
	return output;
}

string makeUnorderedList(const regex& reg, vector<string>& elements, int& i, int  depth, currentHtmlElement& elementType) {
	string output = "";

	if (elementType != UNORDERDLIST) {
		elementType = UNORDERDLIST;
		output += "<ul>\n";

	}
	else if (depth > listDepth) {
		output += "<ul>\n";
		listDepth++;
	}
	output += "<li> " + regex_replace(elements[i], reg, " ") + "</li>\n";

	if ((!regex_search(elements[i+1],reg) && listDepth > 0)) {
		output += "</ul>\n";
		listDepth--;
	}
	else if (!regex_search(elements[i + 1], regex("(^ *[-+*] )|(^\t[-+*] )"))) {
		output += "</ul>\n";
		elementType = NOTINUSE;
	}
	return output;

}
string convertToLink(string mdString){
	if (regex_search(mdString, regex("\\[.*\\]\\(.*\\)"))) {

		if (regex_search(mdString, regex("\\!\\[.*\\]\\(.*\\)"))) {
			smatch match1;
			smatch match2;

			regex_search(mdString, match1, regex("\\[.*\\]"));
			regex_search(mdString, match2, regex("\\(.*\\)"));

			string link = match2.str(0).substr(1, match2.str(0).length() - 2);
			string altText = match1.str(0).substr(1, match1.str(0).length() - 2);
			string fileType = link.substr(link.length() - 5, link.length() - 1);

			for (int i = 0; i < fileType.length(); i++)
				fileType[i] = toupper(fileType[i]);

			if (strcmp(fileType.substr(1, 4).c_str(), ".MP4") == 0 ||
				strcmp(fileType.substr(1, 4).c_str(), ".OGG") == 0
				) {
				mdString = " <video> <source src = \"" + link + "\" type = \"video/" + fileType.substr(2, 4) + "\">" + altText + "</video>\n ";
			}
			else if (strcmp(fileType.substr(0, 4).c_str(), ".WEBM") == 0)
			{
				mdString = " <video> <source src = \"" + link + "\" type = \"video/" + fileType.substr(1, 4) + "\">" + altText + "</video>\n ";
			}
			else if (regex_search(mdString, regex("https://www\\.youtube\\.com")) || regex_search(mdString, regex("youtu.be"))) {
				smatch match1;
				string id = "";
				if (regex_search(mdString, match1, regex("youtu.be.*"))) {
					id = match1.str(0).substr(9, 11);
				}
				else if (regex_search(link, match1, regex("v=.*$"))) {
					id = match1.str(0).substr(2);
				}
				else {
					regex_search(link, match1, regex("embed/.*$"));
					id = match1.str(0).substr(6);
				}
                mdString = "<div>\n<iframe src=\"https://www.youtube.com/embed/"+ id +"\" allowfullscreen ></iframe>\n</div>\n";
				//mdString = "<iframe src = \"https://www.youtube.com/embed/" + id + "\" title = \"YouTube video player\" frameborder = \"0\" allow = \"accelerometer; autoplay; clipboard - write; encrypted - media; gyroscope; picture - in - picture; web - share\"allowfullscreen>< / iframe>";
			}
			else {



				link = regex_replace(link, regex("\\\\"), "/");

				std::filesystem::path pahtToImage = std::filesystem::current_path() / link;
				smatch match1;
				path = regex_replace(path, regex("\\\\"), "/");

				regex_search(link, match1, regex("/[^/]*$"));
				string filename = match1.str(0).substr(1);

				smatch match2;
				regex_search(path, match2, regex("^.*/"));
				string relativePath = "";

				if(match2.str(0).length() >= 1){
					relativePath = match2.str(0);
				}
				std::filesystem::copy(relativePath + link, "site/assets/temp/" + filename);
				mdString = "<img src = \"assets/temp/" + filename + "\" alt = \"" + altText + "\">";
			}

		}

		else {


			smatch match1;
			smatch match2;

			regex_search(mdString, match1, regex("\\[[^\\[]*\\]\\("));
			regex_search(mdString, match2, regex("\\(.*\\)"));

            string altText = match1.str(0).substr(1);
            string link = match2.str(0).substr(1);
			mdString = "<a href=\"" + link.substr(0,link.length()-1) + "\">" + altText.substr(0,altText.length() - 2) + "</a>\n";
		}

	}
    return mdString;
}

string convertLineToTitle(string mdString) {
	if (mdString[0] == '#') {
		int i = 1;
		while (mdString[i] == '#' || mdString[i] == ' ') {
			i += 1;
		}
		if (mdString[i - 1] == ' ') {
            extraDivsToClose ++;
			return "<h" + to_string(i - 1) + ">" + mdString.substr(i, string::npos) + "</h" + to_string(i - 1) + ">";//\n<div>\n";
		}
		else {
			return "";
		}
	}
	if (regex_search(mdString, regex("^[a-zA-Z]"))) {
		mdString = "<p>" + mdString + "</p>";
		smatch match;
		if (regex_search(mdString, match, regex("\\[\\^[0-9]+\\]"))) {
			string ref = match.str(0).substr(2, match.str(0).length() - 3);
			mdString = regex_replace(mdString, regex("\\[\\^[0-9]+\\]"), "<a class=\"refLink\" href=\"#ref" + ref + "\"><sup>" + ref + "</sup></a>\n");
		}


	}



	mdString = regex_replace(mdString, regex("\\\\\\*"), "&#42;");

	mdString = regex_replace(mdString, regex("\\*\\*"), "<b>", regex_constants::format_first_only);
	mdString = regex_replace(mdString, regex("\\*\\*"), "</b>", regex_constants::format_first_only);

	mdString = regex_replace(mdString, regex("\\*"), "<i>", regex_constants::format_first_only);
	mdString = regex_replace(mdString, regex("\\*"), "</i>", regex_constants::format_first_only);

	mdString = regex_replace(mdString, regex("~~"), "<s>", regex_constants::format_first_only);
	mdString = regex_replace(mdString, regex("~~"), "</s>", regex_constants::format_first_only);


	// will apply all styling first and then add as ref
	smatch match;
	if (regex_search(mdString, match, regex("^\\[\\^[0-9]+\\]:"))) {
		string ref = match.str(0).substr(2, match.str(0).length() - 4);
		refrences += "<cite id=\"ref" + ref + "\" class=\"ref\" >\n" + ref + ": "+ convertToLink(mdString.substr(5, mdString.length() - 1)) + "</cite>\n";
		mdString = "";

	}else{
        mdString = convertToLink(mdString);
    }
	return mdString;
}


vector<string> convertElementToHtml(vector<string> elements) {
	enum currentHtmlElement elementType = NOTINUSE;
	vector<string> html;
	vector<int> seperatorsInslideCount;
	for (int i = 0; i < elements.size(); i++) {
	
        if (regex_search(elements[i], regex("<h[0-9]>|<ins>|<sub>|<sup>|<p>|<iframe|<pre|<br"))) {
			//html.push_back(elements[i] + "\n");
			
		}else{
            elements[i] = regex_replace(elements[i],regex("<"), "&lt;");
            elements[i] = regex_replace(elements[i],regex(">"), "&gt;");

        }

    	if (regex_search(elements[i], regex("^```")) || elementType == CODEBLOCK) {
			html.push_back(getCodeblock(elements[i], elementType));
		}

		else if (regex_search(elements[i], regex("^---"))) {
			int slideSeperatorLength = 2;
			for (int j = 2; elements[i][j] == '-'; j++) {
				slideSeperatorLength++;
			}
            for (int j = 0; j < extraDivsToClose;j++){
                //html.push_back("</div>\n");
            }
            extraDivsToClose = 0;

			if (seperatorsInslideCount.size() == 0) {
            
				seperatorsInslideCount.push_back(slideSeperatorLength);
                if(html.size() == 0){
                	html.push_back("<div class=\"slide first-slide\" style=\"visibility: hidden\">\n");
                }else{
	                html.push_back("<div class=\"slide\" style=\"visibility: hidden\">\n");
                }
			}
			else if (seperatorsInslideCount[seperatorsInslideCount.size() - 1] == slideSeperatorLength) {
				seperatorsInslideCount.pop_back();
				html.push_back("</div> \n");
			}
			else {
				seperatorsInslideCount.push_back(slideSeperatorLength);
				html.push_back("<div>\n");
			}

		}
		else if(regex_search(elements[i], regex("^- \\["))){
		  //   cout << elements[i] + "\n";
			 // what do i do with these??
		}

		else if (regex_search(elements[i],regex("^[-+*] "))) {
			html.push_back(makeUnorderedList(regex("^[-+*] "), elements, i, 0, elementType));
		}
		else if (regex_search(elements[i], regex("(^ {" + to_string(spacesForOneTab) + "}[-+*] )|(^\t[-+*] )"))) {
			html.push_back(makeUnorderedList(regex("(^ {" + to_string(spacesForOneTab) + "}[-+*] )|(^\t[-+*] )"), elements, i, 1, elementType));
		}
		else if (regex_search(elements[i], regex("^[0-9]+\\. |^[a-z]\\."))) {
			html.push_back(makeOrderedList(regex("^[0-9]+\\. |^[a-z]\\."), elements, i, 0, elementType));
		}
		else if (regex_search(elements[i], regex("^\t[0-9]+\\. |^ {"+ to_string(spacesForOneTab) +"}[0-9]+\\. |^\t[a-z]\\.|^ {"+ to_string(spacesForOneTab) +"}[a-z]\\."))) {
			html.push_back(makeOrderedList(regex("^ {" + to_string(spacesForOneTab) + "}[0-9]+\\. |^\t[a-z]\\."), elements, i, 1, elementType));
		}   
		else if (regex_search(elements[i], regex("^> "))) {
			html.push_back(getQuote(elements, i, elementType));
		}
				else {
			html.push_back(convertLineToTitle(elements[i]));
		}
	}


	string refClass = "";
	//add refrences back in 
	if (showRef)
	{
		refClass = "slide";
	}
    if(refrences.length() > 2){
	html.push_back("<div class=\"refSlide "+ refClass +"\" id=\"refrences\" style=\"visibility: hidden;\">\n" + refrences + "<div>\n");
    }

    return html;

}

static void fn(struct mg_connection* c, int ev, void* ev_data) {
	if (ev == MG_EV_HTTP_MSG) {  // New HTTP request received
		struct mg_http_message* hm = (struct mg_http_message*)ev_data;  // Parsed HTTP request
		struct mg_http_serve_opts opts = { .root_dir = "./site" };  // For all other URLs,
		mg_http_serve_dir(c, hm, &opts);                     // Serve static files
	}
}





int main(int argumentCount, char* arguments[]) {
	for (const auto& entry : std::filesystem::directory_iterator("site/assets/temp/")){
		std::filesystem::remove_all(entry.path());
    }

	if (argumentCount == 1) {
		cout << help << endl;
		return 0;
	}

	for (int i = 0; i < argumentCount; i++) {
		if (regex_search(arguments[i], regex("(^-v)|(^--version)"))) {
			cout << currentVersion << endl;
			return 0;
		}
		if (regex_search(arguments[i], regex("(^-r)|(^--references)"))) {
			showRef = true;
		}
		if (regex_search(arguments[i], regex("(^-h)|(^--help)"))) {
			cout << help << endl;
			return 0;
		}
		if (regex_search(arguments[i], regex("(^-t)|(^--tab)"))) {
			if (i < argumentCount && regex_search(arguments[i + 1], regex("[0-9]*"))) {
				i++;
				spacesForOneTab = stoi(arguments[i]);
			}
			else if (regex_search(arguments[i], regex("([0-9]$)")))
			{
				spacesForOneTab = stoi(arguments[i]);
			}
		}

	}


	if (!filesystem::exists(arguments[1])) {
		cerr << "file: \"" << arguments[1] << "\" does not exist: exiting" << endl;
		return 0;
	}


	ifstream file(arguments[1]);
    path = arguments[1];
	if (!file.is_open()) {
		cerr << "Error opening the file!";
		return 1;
	}

	vector<string> contents;
	string s;
	while (getline(file, s)) {
		contents.push_back(s);
	}
	file.close();
	//instead of fixing the program just add one more line containing nothing
	contents.push_back("\n");
	vector<string> html = convertElementToHtml(contents);

	ifstream htmlTemplate("templateSite/index.html");
    // Create and open a text file
    ofstream index_html("site/index.html");
    
    string line = "";
    while(getline(htmlTemplate,line)){
        index_html << line + "\n";
        if(regex_search(line,regex("<body>"))){
            for(int j =0; j < html.size(); j++){
                index_html << html[j];
            }
        }   

    }
    index_html.close();
    cout << "presentation running at:\n"<< "\x1B[32mhttp://localhost:8000\033[0m\t\t" <<endl; 
    




    //mongoose
	struct mg_mgr mgr; // Mongoose event manager. Holds all connections
    mg_mgr_init(&mgr);  // Initialise event manager
	mg_http_listen(&mgr, "http://0.0.0.0:8000", fn, NULL);  // Setup listener
	for (;;) {
		mg_mgr_poll(&mgr, 1000);  // Infinite event loop
	}





	return 0;
}


