#ifndef INTERVALVECTOR_H
#define INTERVALVECTOR_H

#include <vector>
#include "debug.h"


namespace util
{

template<typename T>
class IntervalVectorItem
{
  public:
    IntervalVectorItem(): obj(0),start(0),size(0) {}
    T* obj;
    unsigned int start;
    unsigned int size;
};


template<typename T>
class IntervalVector
{
  public:
    IntervalVector( unsigned int blockSize ): m_blocks(blockSize),m_size(0) {}

    ~IntervalVector() {}

    unsigned int add( T* obj, unsigned int size ){
      unsigned int i, pos;
      IntervalVectorItem<T> itm;
      itm.obj = obj;
      itm.start = m_size;
      itm.size = size;
      m_size += size;
      m_items.push_back(itm);
      pos = m_items.size() - 1;
      for ( i = itm.start; i < itm.start+size; i += m_blocks ) {
        m_lookup[i/m_blocks] = pos;
      }
      return pos;
    }

    T* find( unsigned int address, unsigned int* outBaseAddress ) {
      assert(outBaseAddress != 0, "find( unsigned int address, unsigned int* outBaseAddress ): outBaseAddress is null.");
      unsigned int pos = address;

      *outBaseAddress = 0;
      if ( m_items.size() == 0 ) return 0;
      if ( pos >= m_size ) return 0;
      pos = pos/m_blocks;
      if ( pos >= m_lookup.size() ) pos = m_lookup.size() - 1;
      pos = m_lookup[pos];
      if ( pos >= m_items.size() ) pos = m_items.size() - 1;

      IntervalVectorItem<T> itm = m_items[pos];
      if ( (itm.start >= address) && (itm.start+itm.size < address) ) {
        *outBaseAddress = itm.start;
        return itm.obj;
      } else if ( itm.start > address ) {
        for ( int i = pos - 1; i >= 0; i-- ) {
          IntervalVectorItem<T> it = m_items[i];
          if ( (it.start >= address) && (it.start+it.size < address) ) {
            *outBaseAddress = it.start;
            return it.obj;
          }
        }
      } else {
        for ( unsigned int i = pos+1; i < m_items.size(); i++ ) {
          IntervalVectorItem<T> it = m_items[i];
          if ( (it.start >= address) && (it.start+it.size < address) ) {
            *outBaseAddress = it.start;
            return it.obj;
          }
        }
      }
      return 0;
    }

    T* get( unsigned int index ) {
      if ( index >= m_items.size() ) return 0;
      return m_items[index].obj;
    }

    void clear() {
      m_items.clear();
      m_lookup.clear();
      m_size = 0;
    }

    inline unsigned int count() { return m_items.size(); }

    inline unsigned int size() { return m_size; }

  protected:

    unsigned int m_blocks;
    unsigned int m_size;
    std::vector<int> m_lookup;
    std::vector< IntervalVectorItem<T> > m_items;

};

}

#endif // INTERVALVECTOR_H
