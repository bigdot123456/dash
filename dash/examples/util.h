#ifndef DASH__EXAMPLES__UTIL_H__INCLUDED
#define DASH__EXAMPLES__UTIL_H__INCLUDED

#include <libdash.h>
#include <string>
#include <sstream>
#include <iomanip>


#define print(stream_expr__) \
  do { \
    std::ostringstream mss; \
    mss << stream_expr__;  \
    std::ostringstream oss; \
    std::istringstream iss(mss.str()); \
    std::string item; \
    while (std::getline(iss, item)) { \
      oss   << "[    " << dash::myid() << " ] "; \
      oss   << item << endl; \
    } \
    cout << oss.str(); \
  } while(0)


template <class ValueRange>
static std::string range_str(
  const ValueRange & vrange,
  int                prec = 4) {
  typedef typename ValueRange::value_type value_t;
  std::ostringstream ss;
  auto idx = dash::index(vrange);
  int        i   = 0;
  for (const auto & v : vrange) {
    ss << std::setw(2) << *(dash::begin(idx) + i) << "|"
       << std::fixed << std::setprecision(prec)
       << static_cast<const value_t>(v) << " ";
    ++i;
  }
  return ss.str();
}

template <class NViewType>
std::string nview_str(
  const NViewType   & nview,
  int                 prec = 2) {
  using value_t   = typename NViewType::value_type;
  auto view_nrows = nview.extents()[0];
  auto view_ncols = nview.extents()[1];
  auto nindex     = dash::index(nview);
  std::ostringstream ss;
  for (int r = 0; r < view_nrows; ++r) {
    ss << '\n' << r << "  ";
    for (int c = 0; c < view_ncols; ++c) {
      int offset = r * view_ncols + c;
      ss << std::fixed << std::setw(3)
         << nindex[offset]
         << " "
         << std::fixed << std::setprecision(prec)
         << static_cast<value_t>(nview[offset])
         << "  ";
    }
  }
  return ss.str();
}

#endif //  DASH__EXAMPLES__UTIL_H__INCLUDED