//-----------------------------------------------------------------------
// <copyright file="AllJoynObjects.h" company="AllSeen Alliance.">
//     Copyright (c) 2012, AllSeen Alliance. All rights reserved.
//
//        Permission to use, copy, modify, and/or distribute this software for any
//        purpose with or without fee is hereby granted, provided that the above
//        copyright notice and this permission notice appear in all copies.
//
//        THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
//        WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
//        MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
//        ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
//        WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
//        ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
//        OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
// </copyright>
//-----------------------------------------------------------------------

#pragma once

using namespace Chat;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Interop;
using namespace AllJoyn;

namespace AllJoynObjects {

//	Encapsulation object for dispatcher to use when printing message to UI
[Windows::Foundation::Metadata::WebHostHiddenAttribute]
public ref class ArgumentObject sealed {
  public:
    ArgumentObject(Platform::String ^ msg, TextBlock ^ tb);
    void OnDispactched();
  private:
    Platform::String ^ text;
    TextBlock ^ textBlock;
};

//	Encapsulation object for dispatcher to use when printing message to chat view of the UI
[Windows::Foundation::Metadata::WebHostHiddenAttribute]
public ref class ChatArg sealed {
  public:
    ChatArg(Platform::String ^ msg, TextBox ^ tb);
    void OnDispactched();
  private:
    Platform::String ^ text;
    TextBox ^ textBox;
};

//	Bus Object which handles all chat signals received and sent to other chat apps
public ref class ChatObject sealed {
  public:
    ChatObject(BusAttachment ^ busAtt, Platform::String ^ path);

    //	Called when a 'chat' signal is recieved, then outputs message to user
    void ChatSignalHandler(InterfaceMember ^ member, Platform::String ^ srcPath, Message ^ message);

    //	Called when the user requests to send a message over a channel
    void SendChatMessage(Platform::String ^ msg);

    //	Send a signal with given message to the specified sessionId
    void chatSignal(unsigned int sessId, Platform::String ^ msg);

    //	Get the current system time in string format
    Platform::String ^ getTime();

    property BusObject ^ GetBusObject { BusObject ^ get(); }
  private:
    BusObject ^ busObject;                      //Primary bus object implementing interface over the bus
    InterfaceMember ^ signalMember;     //Signal member of the chat interface
};


// Bus Listener which handles all bus events of interest
public ref class MyBusListener sealed {
  public:
    MyBusListener(BusAttachment ^ busAtt);

    // Called by the bus when an external bus is discovered that is advertising a well-known
    // name that this attachment has registered interest in via a DBus call to
    // org.alljoyn.Bus.FindAdvertisedName
    void FoundAdvertisedName(Platform::String ^ wellKnownName, TransportMaskType transport, Platform::String ^ namePrefix);
    // Called by the bus when an advertisement previously reported through FoundName has become
    // unavailable.
    void LostAdvertisedName(Platform::String ^ wellKnownName, TransportMaskType transport, Platform::String ^ namePrefix);
    // Called when the owner of a well-known name changes
    void NameOwnerChanged(Platform::String ^ busName, Platform::String ^ previousOwner, Platform::String ^ newOwner);

    // Called when there's been a join session request from the client
    bool AcceptSessionJoiner(unsigned short sessionPort, Platform::String ^ joiner, SessionOpts ^ sessionOpts);
    //	Called when a session has been joined by client
    void SessionJoined(unsigned short sessionPort, unsigned int sessId, Platform::String ^ joiner);
    //	Called when bus attachment has been disconnected from the D-Bus
    void BusDisconnected();
    //	Called when bus attachment is stopping
    void BusStopping();
    //	Called by the bus when an existing session becomes disconnected.
    void SessionLost(unsigned int sessId);
    //	Called by the bus when a member of a multipoint session is added.
    void SessionMemberAdded(unsigned int sessionId, Platform::String ^ uniqueName);
    //	Called by the bus when a member of a multipoint session is removed.
    void SessionMemberRemoved(unsigned int sessionId, Platform::String ^ uniqueName);
    //	Called by bus attachment when the bus listener is registered
    void ListenerRegistered(BusAttachment ^ busAtt);
    //	Called by bus attachment when the bus listener is unregistered
    void ListenerUnregistered();

    //	Gets the substring of a WKN to exclude the prefix
    Platform::String ^ GetName(Platform::String ^ wkn);

    property BusListener ^ GetBusListener { BusListener ^ get(); }
    property SessionListener ^ GetSessionListener { SessionListener ^ get(); }
    property SessionPortListener ^ GetSessionPortListener { SessionPortListener ^ get(); }
  private:
    BusListener ^ busListener;                                          //primary listener which handles events occurring over the bus
    SessionListener ^ sessionListener;                          //handles session events
    SessionPortListener ^ sessionPortListener;          //handles session port events
};

}
