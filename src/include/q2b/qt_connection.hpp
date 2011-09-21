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

