#pragma once

#include "sshchannel.h"
#include <QSemaphore>
#include <QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(logsshprocess)

class SshProcess : public SshChannel
{
    Q_OBJECT

protected:
    explicit SshProcess(const QString &name, SshClient *client);
    friend class SshClient;

public:
    virtual ~SshProcess() override;
    void close() override;
    QByteArray result();
    bool isError();

    enum ProcessState {
        Openning,
        Exec,
        Read,
        Close,
        WaitClose,
        Freeing,
        Free,
        Error
    };
    Q_ENUM(ProcessState)
    ProcessState m_pstate {ProcessState::Openning};
    QString m_cmd;


    void setPstate(const ProcessState &pstate);

public slots:
    void runCommand(const QString &cmd);
    void sshDataReceived() override;

private:
    LIBSSH2_CHANNEL *m_sshChannel {nullptr};
    QByteArray m_result;

signals:
    void finished();
    void failed();
};
