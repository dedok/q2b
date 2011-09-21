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

#ifndef QT_CONNECTION_HPP_INCLUDED
#define QT_CONNECTION_HPP_INCLUDED

#include <boost/lexical_cast.hpp>

#include "abstract_qt_connection.hpp" 

class QObject;

class qt_connection : public abstract_qt_connection {
public:
	 qt_connection(QObject* qobject, int signal_idx, int slot_idx) :
		abstract_qt_connection(),
		qobject_(qobject), 
		signal_idx_(signal_idx), 
		name_(),
		id_(),
		connected_(false),
		slot_idx_(slot_idx)
	{
		// TODO replace slow boost::lexical_cast ..
		id_ = boost::lexical_cast<std::string>(this);
		name_ = id_;
	}

	virtual void set_name(const std::string& name) { name_ = name; }
	virtual std::string get_name() const { return name_; }

	virtual std::string get_id() const { return id_; }

	virtual int get_slot_idx() const { return slot_idx_; }
	virtual int get_signal_idx() const { return signal_idx_; }

	virtual bool is_connected() const { return connected_; }

	inline QObject * q_meta() { return qobject_; }

protected :
	virtual void set_connect_state(bool state) { connected_ = state; }

private :
	QObject * qobject_;
	int signal_idx_;

	std::string name_;
	std::string id_;

	bool connected_;
	int slot_idx_;

};

#endif

