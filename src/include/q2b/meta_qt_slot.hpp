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

#ifndef META_QT_SLOT_HPP_INCLUDED 
#define META_QT_SLOT_HPP_INCLUDED

#include <boost/function.hpp>

namespace q2b_private {

template<class T>
class meta_qt_slot;

template<class R>
class meta_qt_slot< R() > {
public :
	typedef boost::function0<R> function_type;
	
	inline explicit meta_qt_slot(function_type const & func) : func_(func) { }

	inline void call(void ** /*args*/ ) const {
		func_(); 
	}

private :
	function_type func_;

};

template<class R, class P1>
class meta_qt_slot< R(P1) > {
public :
	typedef boost::function1<R, P1> function_type;
	typedef typename function_type::arg1_type arg1_type;
 
	inline explicit meta_qt_slot(function_type const & func) : func_(func) { }
	
	inline void call(void ** args) const {
		arg1_type * a1 = static_cast<arg1_type*>(args[1]);
		func_(*a1);
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
	
	inline void call(void ** args) const {
		arg1_type * a1 = static_cast<arg1_type*>(args[1]);
		arg2_type * a2 = static_cast<arg2_type*>(args[2]);
		func_(*a1, *a2);
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
	
	inline explicit meta_qt_slot(function_type const & func) : func_(func) { }
	
	inline void call(void ** args) const {
		arg1_type * a1 = static_cast<arg1_type*>(args[1]);
		arg2_type * a2 = static_cast<arg2_type*>(args[2]);
		arg3_type * a3 = static_cast<arg3_type*>(args[3]);
		func_(*a1, *a2, *a3);
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

	inline explicit meta_qt_slot(function_type const & func) : func_(func) { }
	
	inline void call(void ** args) const {
		arg1_type * a1 = static_cast<arg1_type*>(args[1]);
		arg2_type * a2 = static_cast<arg2_type*>(args[2]);
		arg3_type * a3 = static_cast<arg3_type*>(args[3]);
		arg4_type * a4 = static_cast<arg4_type*>(args[4]);
		func_(*a1, *a2, *a3, *a4);
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
	
	inline explicit meta_qt_slot(function_type const & func) : func_(func) { }
	
	inline void call(void ** args) const {
		arg1_type * a1 = static_cast<arg1_type*>(args[1]);
		arg2_type * a2 = static_cast<arg2_type*>(args[2]);
		arg3_type * a3 = static_cast<arg3_type*>(args[3]);
		arg4_type * a4 = static_cast<arg4_type*>(args[4]);
		arg5_type * a5 = static_cast<arg5_type*>(args[5]);
		func_(*a1, *a2, *a3, *a4, *a5);
	}

private :
	function_type func_;

};

template<class R, class P1, class P2, class P3, class P4, class P5, class P6>
class meta_qt_slot< R(P1, P2, P3, P4, P5, P6) > {
public :
	typedef boost::function6<R, P1, P2, P3, P4, P5, P6> function_type;
	typedef typename function_type::arg1_type arg1_type;
 	typedef typename function_type::arg2_type arg2_type;
	typedef typename function_type::arg3_type arg3_type;
	typedef typename function_type::arg4_type arg4_type;
	typedef typename function_type::arg5_type arg5_type;
	typedef typename function_type::arg6_type arg6_type;

	inline explicit meta_qt_slot(function_type const & func) : func_(func) { }
	
	inline void call(void ** args) const {
		arg1_type * a1 = static_cast<arg1_type*>(args[1]);
		arg2_type * a2 = static_cast<arg2_type*>(args[2]);
		arg3_type * a3 = static_cast<arg3_type*>(args[3]);
		arg4_type * a4 = static_cast<arg4_type*>(args[4]);
		arg5_type * a5 = static_cast<arg5_type*>(args[5]);
		arg6_type * a6 = static_cast<arg6_type*>(args[6]);
		func_(*a1, *a2, *a3, *a4, *a5, *a6);
	}

private :
	function_type func_;

};

template<class R, class P1, class P2, class P3, class P4, class P5, class P6, class P7>
class meta_qt_slot< R(P1, P2, P3, P4, P5, P6, P7) > {
public :
	typedef boost::function7<R, P1, P2, P3, P4, P5, P6, P7> function_type;
	typedef typename function_type::arg1_type arg1_type;
 	typedef typename function_type::arg2_type arg2_type;
	typedef typename function_type::arg3_type arg3_type;
	typedef typename function_type::arg4_type arg4_type;
	typedef typename function_type::arg5_type arg5_type;
	typedef typename function_type::arg6_type arg6_type;
	typedef typename function_type::arg7_type arg7_type;

	inline explicit meta_qt_slot(function_type const & func) : func_(func) { }
	
	inline void call(void ** args) const {
		arg1_type * a1 = static_cast<arg1_type*>(args[1]);
		arg2_type * a2 = static_cast<arg2_type*>(args[2]);
		arg3_type * a3 = static_cast<arg3_type*>(args[3]);
		arg4_type * a4 = static_cast<arg4_type*>(args[4]);
		arg5_type * a5 = static_cast<arg5_type*>(args[5]);
		arg6_type * a6 = static_cast<arg6_type*>(args[6]);
		arg7_type * a7 = static_cast<arg7_type*>(args[7]);
		func_(*a1, *a2, *a3, *a4, *a5, *a6, *a7);
	}

private :
	function_type func_;

};

template<
	class R, class P1, class P2, class P3, class P4, 
	class P5, class P6, class P7, class P8
	>
class meta_qt_slot< R(P1, P2, P3, P4, P5, P6, P7, P8) > {
public :
	typedef boost::function8<R, P1, P2, P3, P4, P5, P6, P7, P8> function_type;
	typedef typename function_type::arg1_type arg1_type;
 	typedef typename function_type::arg2_type arg2_type;
	typedef typename function_type::arg3_type arg3_type;
	typedef typename function_type::arg4_type arg4_type;
	typedef typename function_type::arg5_type arg5_type;
	typedef typename function_type::arg6_type arg6_type;
	typedef typename function_type::arg7_type arg7_type;
	typedef typename function_type::arg8_type arg8_type;

	inline explicit meta_qt_slot(function_type const & func) : func_(func) { }
	
	inline void call(void ** args) const {
		arg1_type * a1 = static_cast<arg1_type*>(args[1]);
		arg2_type * a2 = static_cast<arg2_type*>(args[2]);
		arg3_type * a3 = static_cast<arg3_type*>(args[3]);
		arg4_type * a4 = static_cast<arg4_type*>(args[4]);
		arg5_type * a5 = static_cast<arg5_type*>(args[5]);
		arg6_type * a6 = static_cast<arg6_type*>(args[6]);
		arg7_type * a7 = static_cast<arg7_type*>(args[7]);		
		arg8_type * a8 = static_cast<arg8_type*>(args[8]);
		func_(*a1, *a2, *a3, *a4, *a5, *a6, *a7, *a8);
	}

private :
	function_type func_;

};

template<
	class R, class P1, class P2, class P3, class P4, 
	class P5, class P6, class P7, class P8, class P9
	>
class meta_qt_slot< R(P1, P2, P3, P4, P5, P6, P7, P8, P9) > {
public :
	typedef boost::function9<R, P1, P2, P3, P4, P5, P6, P7, P8, P9> function_type;
	typedef typename function_type::arg1_type arg1_type;
 	typedef typename function_type::arg2_type arg2_type;
	typedef typename function_type::arg3_type arg3_type;
	typedef typename function_type::arg4_type arg4_type;
	typedef typename function_type::arg5_type arg5_type;
	typedef typename function_type::arg6_type arg6_type;
	typedef typename function_type::arg7_type arg7_type;
	typedef typename function_type::arg8_type arg8_type;
	typedef typename function_type::arg9_type arg9_type;

	inline explicit meta_qt_slot(function_type const & func) : func_(func) { }
	
	inline void call(void ** args) const {
		arg1_type * a1 = static_cast<arg1_type*>(args[1]);
		arg2_type * a2 = static_cast<arg2_type*>(args[2]);
		arg3_type * a3 = static_cast<arg3_type*>(args[3]);
		arg4_type * a4 = static_cast<arg4_type*>(args[4]);
		arg5_type * a5 = static_cast<arg5_type*>(args[5]);
		arg6_type * a6 = static_cast<arg6_type*>(args[6]);
		arg7_type * a7 = static_cast<arg7_type*>(args[7]);		
		arg8_type * a8 = static_cast<arg8_type*>(args[8]);
		arg9_type * a9 = static_cast<arg9_type*>(args[9]);
		func_(*a1, *a2, *a3, *a4, *a5, *a6, *a7, *a8, *a9);
	}

private :
	function_type func_;

};

}

#endif

