#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/error/en.h"
#include <cstdio>

using namespace rapidjson;

int main(int argc, char *argv[]) {
  for (int i = 1; i < argc; ++i) {
    char *file = argv[i];
    FILE *fp = fopen(file, "rb");
    char readBuffer[65536];
    FileReadStream is(fp, readBuffer, sizeof(readBuffer));

    Document d;
    ParseResult ok = d.ParseStream(is);
    if (!ok) {
      size_t offset = ok.Offset();
      fseek(fp, offset, SEEK_SET);
      char buf[128];
      fread(buf, sizeof(char), 127, fp);
      buf[127] = '\0';
      fprintf(stdout, "%s : %s (offset: %lu)\n--------\n%s\n--------\n", file, GetParseError_En(ok.Code()), ok.Offset(), buf);
    }

    fclose(fp);
  }
  return 0;
}
