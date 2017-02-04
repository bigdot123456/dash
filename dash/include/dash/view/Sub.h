#ifndef DASH__VIEW__SUB_H__INCLUDED
#define DASH__VIEW__SUB_H__INCLUDED

#include <dash/Types.h>
#include <dash/Range.h>

#include <dash/view/ViewMod.h>
#include <dash/view/NViewMod.h>


namespace dash {

// -------------------------------------------------------------------------
// View Modifiers (not coupled with origin memory / index space):
// -------------------------------------------------------------------------

// Sub-space slice, view dimensions maintain domain dimensions

/**
 * \concept{DashViewConcept}
 */
template <
  dim_t SubDim   = 0,
  dim_t NViewDim,
  class OffsetFirstT,
  class OffsetFinalT >
constexpr ViewSubMod<ViewOrigin<NViewDim>, SubDim>
sub(OffsetFirstT begin,
    OffsetFinalT end) {
  return ViewSubMod<ViewOrigin<NViewDim>, SubDim>(begin, end);
}

/**
 * \concept{DashViewConcept}
 */
template <
  dim_t SubDim   = 0,
  dim_t NViewDim,
  class IndexRangeT >
constexpr ViewSubMod<ViewOrigin<NViewDim>, SubDim>
sub(const IndexRangeT & range) {
  return sub<SubDim>(dash::begin(range),
                     dash::end(range));
}

// Sub-space projection, view reduces domain by one dimension

#if 0
/**
 * \concept{DashViewConcept}
 */
template <
  dim_t SubDim = 0,
  class OffsetT >
constexpr ViewSubMod<ViewOrigin, SubDim>
sub(
    OffsetT offset) {
  return ViewSubMod<ViewOrigin, SubDim>(offset);
}
#endif

// -------------------------------------------------------------------------
// View Proxies (coupled with origin memory / index space):
// -------------------------------------------------------------------------

// Sub-space slice, view dimensions maintain domain dimensions

/**
 * \concept{DashViewConcept}
 */
template <
  dim_t SubDim  = 0,
  class DomainT,
  class OffsetFirstT,
  class OffsetFinalT >
constexpr auto
sub(
    OffsetFirstT    begin,
    OffsetFinalT    end,
    const DomainT & domain)
  -> typename std::enable_if<
       dash::view_traits<DomainT>::rank::value == 1,
       ViewSubMod<DomainT, SubDim>
     >::type {
  return ViewSubMod<DomainT, SubDim>(
           domain,
           begin,
           end);
}

#ifdef __TODO__

template <
  dim_t SubDim  = 0,
  class DomainT,
  class OffsetFirstT,
  class OffsetFinalT >
constexpr auto
sub(
    OffsetFirstT    begin,
    OffsetFinalT    end,
    const DomainT & domain)
  -> typename std::enable_if<
       dash::view_traits<DomainT>::rank::value == 1,
       ViewSubMod<const DomainT &, SubDim>
     >::type {
  return ViewSubMod<const DomainT &, SubDim>(
           domain,
           begin,
           end);
}

template <
  dim_t SubDim  = 0,
  class DomainT,
  class OffsetFirstT,
  class OffsetFinalT >
constexpr auto
sub(
    OffsetFirstT    begin,
    OffsetFinalT    end,
    const DomainT && domain)
  -> typename std::enable_if<
       dash::view_traits<DomainT>::rank::value == 1,
       ViewSubMod<DomainT, SubDim>
     >::type {
  return ViewSubMod<DomainT, SubDim>(
           std::forward(domain),
           begin,
           end);
}

#endif

// =========================================================================
// Multidimensional Views
// =========================================================================

template <
  dim_t SubDim  = 0,
  class DomainT,
  class OffsetFirstT,
  class OffsetFinalT >
constexpr auto
sub(
    OffsetFirstT    begin,
    OffsetFinalT    end,
    const DomainT & domain)
  -> typename std::enable_if<
       (dash::view_traits<DomainT>::rank::value > 1),
       NViewSubMod<DomainT, SubDim, dash::view_traits<DomainT>::rank::value>
     >::type {
  return NViewSubMod<
           DomainT,
           SubDim,
           dash::view_traits<DomainT>::rank::value
         >(domain,
           begin,
           end);
}

} // namespace dash

#endif // DASH__VIEW__SUB_H__INCLUDED
