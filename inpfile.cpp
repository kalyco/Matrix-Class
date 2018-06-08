
// class InpFile {
//   public:
//  int fcount = getFileCount();;
//  int * fileArr = new int[fcount];

//   int getFileCount() { 
//   	int number_of_lines = 0;
//   	std::string line;
//   	std::ifstream infile("input.txt");
//   	while (getline(infile, line)) {
//   			++number_of_lines;
//   	}
//   	return number_of_lines;
//   }
//   void setFileArray() {
// 	int i = 0;
// 	int lCount = getFileCount();
// 	std::ifstream infile("input.txt");
// 	std::string line;
// 	while (i < lCount && getline(infile, line)) { 
// 		int n = atoi(line.c_str());
// 		fileArr[i] = n;
// 	};
//   };
// };

// InpFile * fileList = new InpFile;
