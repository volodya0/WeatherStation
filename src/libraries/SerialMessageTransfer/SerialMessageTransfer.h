#ifndef SERIAL_MESSAGE_TRANSFER_H
#define SERIAL_MESSAGE_TRANSFER_H

#include <Arduino.h>

class SerialMessageTransfer
{
public:
    static String WrapMessage(const String &message);
    static uint8_t GetNewMessagesCount();
    static bool CheckNewMessages(const String &input);
    static String GetLastMessage(bool removeFromStack = true);
    static void ClearMessages();
    static void PrintMessagesStack();

private:
    struct MessageData
    {
        String id;
        String message;
    };

    static const size_t MAX_STACK_SIZE = 5;
    static MessageData receivedMessages[MAX_STACK_SIZE];
    static size_t messageCount;
    static size_t currentMessageIndex;

    static String generateUniqueId();
    static bool isIdUnique(const String &id);
};

#endif // SERIAL_MESSAGE_TRANSFER_H
