#ifndef GEOMAP_H
#define GEOMAP_H

#include <string>
#include "QGraph.h"
#include "../kamus/ListVocab.h"
using namespace std;

class GeoMap {

	public:
		GeoMap();
		~GeoMap();
		GeoMap(const GeoMap& other);
		GeoMap& operator=(const GeoMap& other);

		// Setter & getter
		void setQGraph(QGraph& qGraph);
		void setNodeNames(ListVocab* lv);
		QGraph& getQGraph();
		ListVocab* getNodeNames();
		char* getStreetName(int id);
		int getStreetNum();

		void loadStreetNames();
		int getNodeId(const char* nodename);
		int* findPath(int start, int end, int * size);
		void findAllPaths(int start, int end);

	private:
		// string *nodeDesc;
		QGraph qGraph;
		ListVocab *nodeNames;
		char ** edgeNames;
		int edgeNum;
};

#endif