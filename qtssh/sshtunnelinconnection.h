#pragma once

#include "sshchannel.h"
#include <QTcpSocket>
#include <QLoggingCategory>
#include "sshtunneldataconnector.h"

class QTcpSocket;

#define BUFFER_SIZE (128*1024)
Q_DECLARE_LOGGING_CATEGORY(logsshtunnelinconnection)

class SshTunnelInConnection : public SshChannel
{
    Q_OBJECT

public:
    explicit SshTunnelInConnection(const QString &name, SshClient *client, LIBSSH2_CHANNEL* channel, quint16 port, QString hostname);
    virtual ~SshTunnelInConnection() override;
    void close() override;

private:
    SshTunnelDataConnector *m_connector {nullptr};
    LIBSSH2_CHANNEL *m_sshChannel {nullptr};
    QTcpSocket m_sock;
    quint16 m_port;
    QString m_hostname;
    bool m_error {false};

private slots:
    void _socketConnected();
    void _eventLoop();

public slots:
    void sshDataReceived() override;

signals:
    void sendEvent();
};
