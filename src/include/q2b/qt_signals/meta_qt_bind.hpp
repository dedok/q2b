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

#ifndef META_QT_BIND_HPP_INCLUDED
#define META_QT_BIND_HPP_INCLUDED

#include <QObject>

#include <boost/type_traits.hpp>

#include "meta_qt_slot.hpp"

namespace q2b_private {

struct qt_connection_info {
	int signal_idx;
	int slot_idx;
	bool connected;
	QObject * sender;
};

inline bool is_qt_signal_type(char const * signal) {
	return ((signal[0] - '0') & 0x03) == QSIGNAL_CODE ? true : false;
}

template <class Sig>
int get_established_connection(QObject * sender, char const * signal) {
	QByteArray norm_sig = QMetaObject::normalizedSignature(signal + 1);

	if (!is_qt_signal_type(signal)) {
		DEBUG_WARNING("ill connecting %s ; not a signal",  norm_sig.constData())
		return -1;
	}
	
	QMetaObject const * meta_obj = sender->metaObject();
	int const signal_id = meta_obj->indexOfSignal(norm_sig.constData());
	if (signal_id < 0) {
		DEBUG_WARNING("ill connecting %s ; signal does not exist on object %s", 
			norm_sig.constData(), sender->objectName().toStdString().data());
		return -1;
	}

#if defined (Q2B_STRONG_CHECK) 
	QMetaMethod meta_method = meta_obj->method(signal_id);
	int const att_size = int(boost::function_traits<Sig>::arity);
	if  (att_size != meta_method.parameterNames().size()) {
		DEBUG_WARNING("ill connecting %s ; of arguments do not match", 
							norm_sig.constData())
		return -1;
	}
#endif

	return signal_id;
}

}

template<class Sig>
class meta_qt_bind : public QObject {
public:
	typedef boost::function<Sig> function_type;

	inline meta_qt_bind(QObject * sender, int signal_idx, function_type const & func) :
		slot_(func), conn_info_()
	{
		conn_info_.signal_idx = signal_idx;
		conn_info_.slot_idx = metaObject()->methodCount();
		conn_info_.sender = sender;
		conn_info_.connected = QMetaObject::connect(
							sender, conn_info_.signal_idx, this, conn_info_.slot_idx);
	}

#if defined (Q2B_STRONG_CHECK)
	virtual int qt_metacall(QMetaObject::Call callable, int call_id, void ** args) {
		call_id = QObject::qt_metacall(callable, call_id, args);
		if (call_id < 0 || callable != QMetaObject::InvokeMetaMethod)
			return call_id;
		slot_.call(args);
		return -1;
	}
#elif
	virtual int qt_metacall(QMetaObject::Call, int, void ** args) {
		slot_.call(args);
		return -1;
	}

#endif
	inline bool connect() {
		if (!conn_info_.connected)
			return (conn_info_.connected = QMetaObject::connect(conn_info_.sender, 
								conn_info_.signal_idx, this, conn_info_.slot_idx));
		return false;
	}

	inline bool disconnect() {
		if (conn_info_.connected)
			return (conn_info_.connected = !QMetaObject::disconnect(conn_info_.sender, 
					conn_info_.signal_idx, this, conn_info_.slot_idx));
		return false;
	}
	
	inline bool is_connected() const { 
		return conn_info_.connected; 
	} 

	~meta_qt_bind() { 
		disconnect();
	}

private :
	q2b_private::meta_qt_slot<Sig> slot_;
	q2b_private::qt_connection_info conn_info_;	

};

#endif 

