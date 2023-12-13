
#include "include/utility.h"
#include "include/loc.h"
#include "search_runner.h"

SearchRunner::Matcher::Matcher(const std::string& needle): needle{needle}{
  // initialize lps with longest-proper prefix-suffix
  auto size = needle.size();
  lps.resize(size);
  lps[0] = 0;
  for (size_t i=1, j=0; i < size; ++i){
    while (j > 0 && needle[j] != needle[i]){ j = lps[j-1]; }
    if (needle[j] == needle[i]) { ++j; }
    lps[i]=j;
  }
}

bool SearchRunner::Matcher::operator==(char ch) {
  while (curri > 0 && needle[curri] != ch) {
    curri = lps[curri-1];
  }
  if (needle[curri] == ch) ++curri;
  if (curri == needle.size()){ // size matches <=> found match
    curri = lps[curri-1];
    return true;
  }
  return false;
}

void SearchRunner::run(const Search* cmd) {
  if (cmd->needle.size()) { // reset matchers if needle is valid
    auto needle = cmd->needle;
    reverse = (cmd->type == '?');
    matcher = Matcher{needle};
    std::reverse(needle.begin(), needle.end());
    rmatcher = Matcher{needle};
  }
  // go to the next occurrence
  auto tmp = Movement{1,'n'}; 
  rootModeManager.setMode(ModeType::Normal);
  run(&tmp);
}

void SearchRunner::run(const Movement* cmd) {  
  bool useRI = reverse; // whether to use reverse iterator
  if (cmd->type == 'N'){
    useRI = !useRI;
  } else if (cmd->type != 'n'){
    return; // not n,N, so do nothing
  }
  auto count = normalizeCount(cmd->count);
  auto& tab = activeWindow->getTabManager().curr();
  auto cursor = tab.getCursor();
  auto curCol = cursor.getCol(), curRow = cursor.getRow();
  const auto& filebuf = tab.getFilebuf();

  // seek next
  if (useRI){
    rmatcher.reset();
    // start searching so that first possible match is one col to left of curCol
    int startCol = curCol - 2 + static_cast<int>(rmatcher.getNeedle().size());
    startCol = fit(0,filebuf.getLine(curRow).size()-1, startCol);
    auto beg = filebuf.rbegin(curRow, startCol);
    auto end = filebuf.rend();
    auto pos = findNth(count, beg, end, rmatcher);
    // check if hit top
    if (pos == end) {
      rmatcher.reset();
      rootStatus.setMessage("search hit TOP, continuing at BOTTOM");
      auto beg = filebuf.rbegin();
      pos = findNth(count, beg, end, rmatcher);
      if (pos == end) { // needle not matches anything
        rootStatus.setMessage(matcher.getNeedle());
        rootStatus.setError(ErrorCode::patternNotFound);
        return;
      }
    } else {
      rootStatus.setMessage('?' + matcher.getNeedle());
    }
    cursor.translate(pos.getLine(), pos.getCol());
  } else { // use forward iteration
    matcher.reset();
    auto beg = ++filebuf.begin(curRow, curCol);
    auto end = filebuf.end();
    auto pos = findNth(count, beg, end, matcher);
    // check if hit bottom
    if (pos == end) {
      matcher.reset();
      rootStatus.setMessage("search hit BOTTOM, continuing at TOP");
      auto beg = filebuf.begin();
      pos = findNth(count, beg, end, matcher);
      if (pos == end) { // needle not matches anything
        rootStatus.setMessage(matcher.getNeedle());
        rootStatus.setError(ErrorCode::patternNotFound);
        return;
      }
    } else{
      rootStatus.setMessage('/' + matcher.getNeedle());
    }
    cursor.translate(pos.getLine(), pos.getCol()-matcher.getNeedle().size()+1);
  }
  tab.setCursor(cursor,true);
}
