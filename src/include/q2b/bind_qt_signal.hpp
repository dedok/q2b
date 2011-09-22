// q2b is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// q2b is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with q2b.  If not, see <http://www.gnu.org/licenses/>.

#ifndef BIND_QT_SIGNAL_HPP_INCLUDED
#define BIND_QT_SIGNAL_HPP_INCLUDED

#include <boost/function.hpp>

#include "config.hpp"
#include "meta_qt_bind.hpp"

template <class Sig>
inline meta_qt_bind<Sig> * bind_qt_signal(
	QObject * sender, const char * signal, boost::function<Sig> const & func) 
{
	using q2b_private::get_established_connection;
	int const signal_id = get_established_connection<Sig>(sender, signal);
	if (signal_id < 0) return NULL; 
	return new meta_qt_bind<Sig>(sender, signal_id, func);
}

#endif

