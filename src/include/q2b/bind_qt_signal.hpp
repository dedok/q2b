#ifndef BIND_QT_SIGNAL_HPP_INCLUDED
#define BIND_QT_SIGNAL_HPP_INCLUDED

#include <boost/function.hpp>

#include "config.hpp"
#include "qt_connection.hpp"
#include "meta_qt_bind.hpp"

namespace q2b_private {

inline int is_qt_signal_type(char const * signal) {
	return ((signal[0] - '0') & 0x03) == QSIGNAL_CODE ? true : false;
}

template <class Sig>
int is_established_connection(
	QObject * qobject, char const * signal, boost::function<Sig> const & /*func*/) 
{
	QByteArray norm_sig = QMetaObject::normalizedSignature(signal + 1);

	if (!is_qt_signal_type(signal)) {
		DEBUG_WARNING("ill connecting %s ; not a signal",  norm_sig.constData())
		return -1;
	}

	int const signal_id = 
		qobject->metaObject()->indexOfSignal(norm_sig.constData());
	if (signal_id < 0) {
		DEBUG_WARNING("ill connecting %s ; signal does not exist on object %s", 
			norm_sig.constData(), qobject->objectName().toStdString().data());
		return -1;
	}

	QMetaMethod meta_method = qobject->metaObject()->method(signal_id);
	int const att_size = int(boost::function_traits<Sig>::arity);
	if  (att_size != meta_method.parameterNames().size()) {
		DEBUG_WARNING("ill connecting %s ; of arguments do not match", 
							norm_sig.constData())
		return -1;
	}

	return signal_id;
}

}

template <class Sig>
inline qt_connection * bind_qt_signal(
	QObject* qobject, const char* signal, const boost::function<Sig> & func) 
{
	using q2b_private::is_established_connection;
	int const signal_id = is_established_connection(qobject, signal, func);
	if (signal_id < 0) return NULL; 
	return new meta_qt_bind<Sig, qt_connection>(qobject, signal_id, func);
}

template <class Sig, class ConnectionInfo>
inline ConnectionInfo * bind_qt_signal(
	QObject* qobject, const char* signal, const boost::function<Sig> & func)
{
	using q2b_private::is_established_connection;
	int const signal_id = is_established_connection(qobject, signal, func);
	if (signal_id < 0) return NULL; 
	return new meta_qt_bind<Sig, ConnectionInfo>(qobject, signal_id, func);
}

#endif

