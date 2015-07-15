#ifndef _AccessPoint_h_
#define _AccessPoint_h_

#include "Station.h"
CxxBeginNameSpace(Router)

/* class SecondType,  get element's type by iterator. 
   refer to <C++ Templates - The Complete Guide>, chapter 15.2.1 
   "Determining Element Types" for more detail.
 */
template <typename T>
class SecondType // primary template
{
public:
    typedef typename std::iterator_traits<T>::value_type::second_type Type;
};

template<class BaseIterator>
struct MapIterator: public BaseIterator
{
    typedef typename SecondType<BaseIterator>::Type SecondType;
    MapIterator() {}
    MapIterator(BaseIterator& iter): BaseIterator(iter) {}
    SecondType& operator*() const {return BaseIterator::operator ->()->second;}
    SecondType* operator->() const{return &(BaseIterator::operator ->()->second);}
};

enum class Crypt
{
    Wep = 1,
    Wpa = 2,
};

class Ap
{
public:
    typedef MapIterator<std::map<Mac, St>::iterator> Iterator;
    typedef MapIterator<std::map<Mac, St>::const_iterator> ConstIterator;

    Ap(Mac const&, Crypt);
    Ap(Ap const&);
    std::string GetEssid() const;
    void SetEssid(const std::string&);
    Mac const& GetBssid() const;
    Crypt GetCrypt() const;
    void SetCrypt(Crypt crypt);

    std::pair<Iterator, bool> Insert(St const&);
    Iterator Begin();
    Iterator End();
    ConstIterator CBegin() const;
    ConstIterator CEnd() const;

    Iterator Find(Mac const&);
    ConstIterator Find(Mac const&) const;

    /* the following function is provided just for debug */
    void Put(std::ostream& os) const;

private:   
    Ap();

private:
    Mac bssid;
    std::string essid;
    Crypt crypt;
    std::map<Mac, St> stList;
};
std::ostream& operator << (std::ostream& os, Ap const& ap);

class Aps
{
public:
    typedef MapIterator<std::map<Mac, Ap>::iterator> Iterator;
    typedef MapIterator<std::map<Mac, Ap>::const_iterator> ConstIterator;

    std::pair<Iterator, bool> Insert(Ap const&);
    Iterator Begin();
    Iterator End();
    ConstIterator CBegin() const;
    ConstIterator CEnd() const;

    Iterator Find(Mac const&);
    ConstIterator Find(Mac const&) const;

    static Aps& GetInstance();

    /* the following function is provided just for debug */
    void Put(std::ostream& os) const;

private:
    Aps() {}
    std::map<Mac, Ap> apList;
};
std::ostream& operator << (std::ostream& os, Aps const& aps);

CxxEndNameSpace
#endif