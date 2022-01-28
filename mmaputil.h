#ifndef MULTIMAP_UTIL_H
#define MULTIMAP_UTIL_H

#include <map>

template <class Key, class T, class Compare = std::less<Key> >
class multimap_util {
private:
	std::multimap<Key, T, Compare> &_map;

public:
	multimap_util (std::multimap<Key, T, Compare> &m) : _map(m) { }

	multimap_util& erase(T value) {
		for (typename std::multimap<Key, T, Compare>::iterator it = _map.begin(); it != _map.end();) {
			if (it->second == value) {
				_map.erase(it++);
			} else {
				++it;
			}
		}
	
		return *this;
	}

	multimap_util& replace_key(Key &i, Key &j) {
		for (typename std::multimap<Key, T, Compare>::iterator it = _map.begin(); it != _map.end(); ++it) {
			if (it->first == i) {
				_map.insert( std::make_pair( j, it->second ) );
				_map.erase(it);
				break;
			}
		}
	
		return *this;
	}

	multimap_util& replace_value(T &i, T &j) {
		for (typename std::multimap<Key, T, Compare>::iterator it = _map.begin(); it != _map.end(); ++it) {
			if (it->second == i)
				it->second = j;
		}

		return *this;
	}

	multimap_util& swap(Key &i, Key &j)
	{
		T lhs;
		T rhs;

		for (typename std::multimap<Key, T, Compare>::reverse_iterator it = _map.rbegin(); it != _map.rend(); ++it) {
			if (it->first == i)
				lhs = it->second;
			else if (it->first == j)
				rhs = it->second;
		}
	
		_map.find(i)->second = rhs;
		_map.find(j)->second = lhs;

		return *this;
	}
};

#endif