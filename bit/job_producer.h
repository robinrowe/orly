#include <string>
#include <vector>

#include <base/opt.h>
#include <util/timestamp.h>

namespace Jhm {

class TEnv;
class TFile;
class TJob;

struct TJobProducer {
  const char *Name;
  // TODO: Should really be a set...
  std::vector<std::vector<std::string>> OutExtensions;
  std::function<Base::TOpt<TRelPath>(const TRelPath &name)> TryGetInputName;
  std::function<std::unique_ptr<TJob>(TEnv &env, TFile *in_file)> MakeJob;
  Util::TTimestamp CmdTimestamp;
};

} // namespace Jhm