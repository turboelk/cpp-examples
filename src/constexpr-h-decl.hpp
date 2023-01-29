#ifndef CONSTEXPR_H_DECL
#define CONSTEXPR_H_DECL

#define Type(What, Converts)\
  struct What {\
    typedef Converts type;\
    static constexpr const char *name { #What };\
  }

#endif/*CONSTEXPR_H_DECL*/
