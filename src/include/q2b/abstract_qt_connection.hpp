/*
 * Copyright 2011 Soshnikov Vasiliy <dedok.mad@gmail.com>
 *
 * Permission to use, copy, modify, and distribute this software
 * and its documentation for any purpose and without fee is hereby
 * granted, provided that the above copyright notice appear in all
 * copies and that both that the copyright notice and this
 * permission notice and warranty disclaimer appear in supporting
 * documentation, and that the name of the author not be used in
 * advertising or publicity pertaining to distribution of the
 * software without specific, written prior permission.
 *
 * The author disclaim all warranties with regard to this
 * software, including all implied warranties of merchantability
 * and fitness.  In no event shall the author be liable for any
 * special, indirect or consequential damages or any damages
 * whatsoever resulting from loss of use, data or profits, whether
 * in an action of contract, negligence or other tortious action,
 * arising out of or in connection with the use or performance of
 * this software.
 */

#ifndef ABSTRACT_QT_CONNECTION_HPP_INCLUDED
#define ABSTRACT_QT_CONNECTION_HPP_INCLUDED

#include <string>

class abstract_qt_connection {
public :
	abstract_qt_connection() { }
	virtual ~abstract_qt_connection() { }
	
	virtual void set_name(std::string const & name) = 0;
	virtual std::string get_name() const = 0;
	virtual std::string get_id() const = 0;
	
	virtual int get_slot_idx() const = 0;
	virtual int get_signal_idx() const = 0;

	virtual void connect() = 0;		
	virtual void disconnect() = 0;
	virtual bool is_connected() const = 0;

protected :
	virtual void set_connect_state(bool state) = 0;

	abstract_qt_connection(abstract_qt_connection const &);
	abstract_qt_connection & operator=(abstract_qt_connection const &);
};

#endif

