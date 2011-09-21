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

#ifndef META_QT_BIND_HPP
#define META_QT_BIND_HPP

#include <boost/type_traits.hpp>
#include <boost/function/function0.hpp>
#include <boost/function/function1.hpp>
#include <boost/function/function2.hpp>
#include <boost/function/function3.hpp>
#include <boost/function/function4.hpp>
#include <boost/function/function5.hpp>

#include "qt_connection.hpp"

template<class T>
class meta_qt_slot;

template<class R>
class meta_qt_slot< R() > {
public :
	typedef boost::function0<R> function_type;
	
	explicit meta_qt_slot(function_type const & func) : func_(func) { }

	inline void call(QObject * /*sender*/, void ** /*args*/ ) {
		if (func_) func_(); 
	}

private :
	function_type func_;

};

template<class R, class P1>
class meta_qt_slot< R(P1) > {
public :
	typedef boost::function1<R, P1> function_type;
	typedef typename function_type::arg1_type arg1_type;
 
	explicit meta_qt_slot(function_type const & func) : func_(func) { }
	
	inline void call(QObject * /*sender*/, void ** args) {
		arg1_type * a1 = static_cast<arg1_type*>(args[1]);
		if (func_) func_(*a1);
	}

private : 
	function_type func_;

};

template<class R, class P1, class P2>
class meta_qt_slot< R(P1, P2) > {
public :
	typedef boost::function2<R, P1, P2> function_type;
	typedef typename function_type::arg1_type arg1_type;
 	typedef typename function_type::arg2_type arg2_type;

	explicit meta_qt_slot(function_type const & func) : func_(func) { }
	
	inline void call(QObject * /*sender*/, void ** args) {
		arg1_type * a1 = static_cast<arg1_type*>(args[1]);
		arg2_type * a2 = static_cast<arg2_type*>(args[2]);
		if (func_) func_(*a1, *a2);
	}

private :
	function_type func_;

};

template<class R, class P1, class P2, class P3>
class meta_qt_slot< R(P1, P2, P3) > {
public :
	typedef boost::function3<R, P1, P2, P3> function_type;
	typedef typename function_type::arg1_type arg1_type;
 	typedef typename function_type::arg2_type arg2_type;
	typedef typename function_type::arg3_type arg3_type;
	
	explicit meta_qt_slot(function_type const & func) : func_(func) { }
	
	inline void call(QObject * /*sender*/, void ** args) {
		arg1_type * a1 = static_cast<arg1_type*>(args[1]);
		arg2_type * a2 = static_cast<arg2_type*>(args[2]);
		arg3_type * a3 = static_cast<arg3_type*>(args[3]);
		if (func_) func_(*a1, *a2, *a3);
	}

private :
	function_type func_;

};

template<class R, class P1, class P2, class P3, class P4>
class meta_qt_slot< R(P1, P2, P3, P4) > {
public :
	typedef boost::function4<R, P1, P2, P3, P4> function_type;
	typedef typename function_type::arg1_type arg1_type;
 	typedef typename function_type::arg2_type arg2_type;
	typedef typename function_type::arg3_type arg3_type;
	typedef typename function_type::arg4_type arg4_type;

	explicit meta_qt_slot(function_type const & func) : func_(func) { }
	
	inline void call(QObject * /*sender*/, void ** args) {
		arg1_type * a1 = static_cast<arg1_type*>(args[1]);
		arg2_type * a2 = static_cast<arg2_type*>(args[2]);
		arg3_type * a3 = static_cast<arg3_type*>(args[3]);
		arg4_type * a4 = static_cast<arg4_type*>(args[4]);
		if (func_) func_(*a1, *a2, *a3, *a4);
	}

private :
	function_type func_;

};

template<class R, class P1, class P2, class P3, class P4, class P5>
class meta_qt_slot< R(P1, P2, P3, P4, P5) > {
public :
	typedef boost::function5<R, P1, P2, P3, P4, P5> function_type;
	typedef typename function_type::arg1_type arg1_type;
 	typedef typename function_type::arg2_type arg2_type;
	typedef typename function_type::arg3_type arg3_type;
	typedef typename function_type::arg4_type arg4_type;
	typedef typename function_type::arg5_type arg5_type;
	
	explicit meta_qt_slot(function_type const & func) : func_(func) { }
	
	inline void call(QObject * /*sender*/, void ** args) {
		arg1_type * a1 = static_cast<arg1_type*>(args[1]);
		arg2_type * a2 = static_cast<arg2_type*>(args[2]);
		arg3_type * a3 = static_cast<arg3_type*>(args[3]);
		arg4_type * a4 = static_cast<arg4_type*>(args[4]);
		arg5_type * a5 = static_cast<arg4_type*>(args[5]);
		if (func_) func_(*a1, *a2, *a3, *a4, *a5);
	}

private :
	function_type func_;

};

template<class SIG, class ConnectorInfo>
class meta_qt_bind : public QObject, public ConnectorInfo {
public:
	typedef ConnectorInfo connector_info_type;
	typedef boost::function<SIG> function_type;
	
	meta_qt_bind(QObject* qobject, int signal_idx, function_type const & func) :
		QObject(qobject), 
		connector_info_type(qobject, signal_idx, metaObject()->methodCount()), 
		func_(func),
		slot_(NULL)
	{
		slot_ = new meta_qt_slot<SIG>(func);
		connect();
	}

	~meta_qt_bind() {
		delete slot_; slot_ = NULL;
	}

	inline int qt_metacall(QMetaObject::Call call_able, int call_id, void ** args) {
		call_id = QObject::qt_metacall(call_able, call_id, args);
		if ( call_id < 0 || call_able != QMetaObject::InvokeMetaMethod )
			return call_id;
		slot_->call(sender(), args);
		return -1;
	}

	virtual void connect() {
		bool const state = 
			QMetaObject::connect(this->q_meta(), 
				this->get_signal_idx(), this, this->get_slot_idx());
		this->set_connect_state(state);
	}

	virtual void disconnect() {
		bool const state =
			!QMetaObject::disconnect(this->q_meta(), 
					this->get_signal_idx(), this, this->get_slot_idx());
		this->set_connect_state(state);
	}

private :
	function_type func_;
	meta_qt_slot<SIG> * slot_;

};

#endif 

