#include "SerialMessageTransfer.h"

size_t SerialMessageTransfer::messageCount = 0;
size_t SerialMessageTransfer::currentMessageIndex = 0;
SerialMessageTransfer::MessageData SerialMessageTransfer::receivedMessages[MAX_STACK_SIZE];

String SerialMessageTransfer::WrapMessage(const String &message)
{
    String wrappedMessage = "$(";
    wrappedMessage += generateUniqueId();
    wrappedMessage += "|";
    wrappedMessage += message;
    wrappedMessage += ")$";
    return wrappedMessage;
}

size_t SerialMessageTransfer::GetNewMessagesCount()
{
    return currentMessageIndex;
}

bool SerialMessageTransfer::CheckNewMessages(const String &input)
{
    if (input.length() < 10)
    {
        return false;
    }

    int start = input.indexOf('$(');
    bool isNewMessageAdded = false;

    Serial.println("SerialMessageTransfer::checkNewMessages -> " + input);

    while (start != -1)
    {
        int sep = input.indexOf('|', start);
        int end = input.indexOf('$)', sep);

        if (end == -1 || sep == -1)
        {
            Serial.println("Invalid message format");
            return isNewMessageAdded;
        }

        String id = input.substring(start + 1, sep);
        if (!isIdUnique(id))
        {
            Serial.println("Received message with duplicate or old ID: " + id);
            return isNewMessageAdded;
        }

        String message = input.substring(sep + 1, end);

        if (message.length() <= 0)
        {
            return isNewMessageAdded;
        }

        receivedMessages[currentMessageIndex].id = id;
        receivedMessages[currentMessageIndex].message = message;
        currentMessageIndex = (currentMessageIndex + 1) % MAX_STACK_SIZE;
        if (messageCount < MAX_STACK_SIZE)
        {
            ++messageCount;
        }

        isNewMessageAdded = true;
        start = input.indexOf('$(', end);
    }

    return isNewMessageAdded;
}

String SerialMessageTransfer::GetLastMessage(bool removeFromStack)
{
    if (messageCount == 0)
    {
        return "";
    }

    size_t lastIndex = (currentMessageIndex + MAX_STACK_SIZE - 1) % MAX_STACK_SIZE;
    String lastMessage = receivedMessages[lastIndex].message;
    if (removeFromStack)
    {
        currentMessageIndex = lastIndex;
        --messageCount;
    }
    return lastMessage;
}

void SerialMessageTransfer::ClearMessages()
{
    messageCount = 0;
    currentMessageIndex = 0;
}

void SerialMessageTransfer::PrintMessagesStack()
{
    Serial.println("--- Message Stack ---");
    size_t index = currentMessageIndex - 1;
    for (size_t i = 0; i < messageCount; ++i)
    {
        Serial.print("ID: ");
        Serial.println(receivedMessages[index].id);
        Serial.print("Message: ");
        Serial.println(receivedMessages[index].message);
        Serial.println("---------------------");
        index = (index + MAX_STACK_SIZE - 1) % MAX_STACK_SIZE;
    }
}

String SerialMessageTransfer::generateUniqueId()
{
    static unsigned int counter = 0;
    return String(counter++);
}

bool SerialMessageTransfer::isIdUnique(const String &id)
{
    size_t index = currentMessageIndex;
    for (size_t i = 0; i < messageCount; ++i)
    {
        if (receivedMessages[index].id.equals(id))
        {
            return false;
        }
        index = (index + MAX_STACK_SIZE - 1) % MAX_STACK_SIZE;
    }
    return true;
}
