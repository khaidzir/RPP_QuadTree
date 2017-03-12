#ifndef GEOMAP_H
#define GEOMAP_H

#include <string>
#include "QGraph.h"
using namespace std;

class GeoMap {

	public:
		GeoMap();
		~GeoMap();
		GeoMap(const GeoMap& other);
		GeoMap& operator=(const GeoMap& other);
		void setQGraph(QGraph qGraph);

		int* findPath(int start, int end, int * size);
		void findAllPaths(int start, int end);

	private:
		// string *nodeDesc;
		QGraph qGraph;
};

#endif