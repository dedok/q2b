#include <QTime>
#include <QCoreApplication>

#include <QtDebug>

#include <QMetaMethod>
#include <q2b/bind_qt_signal.hpp>
#include <boost/bind.hpp>

const quint64 c_N = 10000000;

class Sender : public QObject {
	Q_OBJECT
public:
	void askShow() { emit needShow(); }

signals:
	void needShow();
};

class Client { //: public QObject {
//Q_OBJECT
public:
	Client() {
		Sender *p = &m_S;
		bind_qt_signal<void()>(p, SIGNAL(needShow()),
			boost::bind(&Client::show, this));
//		connect(&m_S, SIGNAL(needShow()), SLOT(show()));
	}
	void start() {
		m_I = 0;
		m_T.start();
		for (quint64 i=0; i<c_N; ++i) m_S.askShow();
	}

//private slots:
	void show() {
		if (++m_I == c_N) qDebug() << m_T.elapsed();
	}

private:
	Sender m_S;
	QTime m_T;
	quint64 m_I;

};

int main(int argc, char *argv[]) {
	QCoreApplication a(argc, argv);
	Client c;
	c.start();	
	return a.exec();
}

#include "main.moc"

