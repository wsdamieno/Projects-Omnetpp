//
// Generated file, do not edit! Created by nedtool 4.6 from src/node/communication/routing/leachRouting/LeachRoutingPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "LeachRoutingPacket_m.h"

USING_NAMESPACE


// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




// Template rule for outputting std::vector<T> types
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

EXECUTE_ON_STARTUP(
    cEnum *e = cEnum::find("LeachRoutingPacket_Type");
    if (!e) enums.getInstance()->add(e = new cEnum("LeachRoutingPacket_Type"));
    e->insert(LEACH_ROUTING_ADV_PACKET, "LEACH_ROUTING_ADV_PACKET");
    e->insert(LEACH_ROUTING_JOIN_PACKET, "LEACH_ROUTING_JOIN_PACKET");
    e->insert(LEACH_ROUTING_TDMA_PACKET, "LEACH_ROUTING_TDMA_PACKET");
    e->insert(LEACH_ROUTING_DATA_PACKET, "LEACH_ROUTING_DATA_PACKET");
    e->insert(LEACH_ROUTING_DATA_SINGLE_PACKET, "LEACH_ROUTING_DATA_SINGLE_PACKET");
    e->insert(LEACH_ROUTING_DATA_AGGREGATED_PACKET, "LEACH_ROUTING_DATA_AGGREGATED_PACKET");
);

Register_Class(LeachRoutingPacket);

LeachRoutingPacket::LeachRoutingPacket(const char *name, int kind) : ::RoutingPacket(name,kind)
{
    this->LeachRoutingPacketKind_var = 0;
}

LeachRoutingPacket::LeachRoutingPacket(const LeachRoutingPacket& other) : ::RoutingPacket(other)
{
    copy(other);
}

LeachRoutingPacket::~LeachRoutingPacket()
{
}

LeachRoutingPacket& LeachRoutingPacket::operator=(const LeachRoutingPacket& other)
{
    if (this==&other) return *this;
    ::RoutingPacket::operator=(other);
    copy(other);
    return *this;
}

void LeachRoutingPacket::copy(const LeachRoutingPacket& other)
{
    this->LeachRoutingPacketKind_var = other.LeachRoutingPacketKind_var;
}

void LeachRoutingPacket::parsimPack(cCommBuffer *b)
{
    ::RoutingPacket::parsimPack(b);
    doPacking(b,this->LeachRoutingPacketKind_var);
}

void LeachRoutingPacket::parsimUnpack(cCommBuffer *b)
{
    ::RoutingPacket::parsimUnpack(b);
    doUnpacking(b,this->LeachRoutingPacketKind_var);
}

int LeachRoutingPacket::getLeachRoutingPacketKind() const
{
    return LeachRoutingPacketKind_var;
}

void LeachRoutingPacket::setLeachRoutingPacketKind(int LeachRoutingPacketKind)
{
    this->LeachRoutingPacketKind_var = LeachRoutingPacketKind;
}

class LeachRoutingPacketDescriptor : public cClassDescriptor
{
  public:
    LeachRoutingPacketDescriptor();
    virtual ~LeachRoutingPacketDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(LeachRoutingPacketDescriptor);

LeachRoutingPacketDescriptor::LeachRoutingPacketDescriptor() : cClassDescriptor("LeachRoutingPacket", "RoutingPacket")
{
}

LeachRoutingPacketDescriptor::~LeachRoutingPacketDescriptor()
{
}

bool LeachRoutingPacketDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<LeachRoutingPacket *>(obj)!=NULL;
}

const char *LeachRoutingPacketDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int LeachRoutingPacketDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int LeachRoutingPacketDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *LeachRoutingPacketDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "LeachRoutingPacketKind",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int LeachRoutingPacketDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='L' && strcmp(fieldName, "LeachRoutingPacketKind")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *LeachRoutingPacketDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *LeachRoutingPacketDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "LeachRoutingPacket_Type";
            return NULL;
        default: return NULL;
    }
}

int LeachRoutingPacketDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    LeachRoutingPacket *pp = (LeachRoutingPacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string LeachRoutingPacketDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    LeachRoutingPacket *pp = (LeachRoutingPacket *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getLeachRoutingPacketKind());
        default: return "";
    }
}

bool LeachRoutingPacketDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    LeachRoutingPacket *pp = (LeachRoutingPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setLeachRoutingPacketKind(string2long(value)); return true;
        default: return false;
    }
}

const char *LeachRoutingPacketDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    };
}

void *LeachRoutingPacketDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    LeachRoutingPacket *pp = (LeachRoutingPacket *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(LeachRoutingJoinPacket);

LeachRoutingJoinPacket::LeachRoutingJoinPacket(const char *name, int kind) : ::LeachRoutingPacket(name,kind)
{
    this->priorityLevel_var = 0;
}

LeachRoutingJoinPacket::LeachRoutingJoinPacket(const LeachRoutingJoinPacket& other) : ::LeachRoutingPacket(other)
{
    copy(other);
}

LeachRoutingJoinPacket::~LeachRoutingJoinPacket()
{
}

LeachRoutingJoinPacket& LeachRoutingJoinPacket::operator=(const LeachRoutingJoinPacket& other)
{
    if (this==&other) return *this;
    ::LeachRoutingPacket::operator=(other);
    copy(other);
    return *this;
}

void LeachRoutingJoinPacket::copy(const LeachRoutingJoinPacket& other)
{
    this->priorityLevel_var = other.priorityLevel_var;
}

void LeachRoutingJoinPacket::parsimPack(cCommBuffer *b)
{
    ::LeachRoutingPacket::parsimPack(b);
    doPacking(b,this->priorityLevel_var);
}

void LeachRoutingJoinPacket::parsimUnpack(cCommBuffer *b)
{
    ::LeachRoutingPacket::parsimUnpack(b);
    doUnpacking(b,this->priorityLevel_var);
}

int LeachRoutingJoinPacket::getPriorityLevel() const
{
    return priorityLevel_var;
}

void LeachRoutingJoinPacket::setPriorityLevel(int priorityLevel)
{
    this->priorityLevel_var = priorityLevel;
}

class LeachRoutingJoinPacketDescriptor : public cClassDescriptor
{
  public:
    LeachRoutingJoinPacketDescriptor();
    virtual ~LeachRoutingJoinPacketDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(LeachRoutingJoinPacketDescriptor);

LeachRoutingJoinPacketDescriptor::LeachRoutingJoinPacketDescriptor() : cClassDescriptor("LeachRoutingJoinPacket", "LeachRoutingPacket")
{
}

LeachRoutingJoinPacketDescriptor::~LeachRoutingJoinPacketDescriptor()
{
}

bool LeachRoutingJoinPacketDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<LeachRoutingJoinPacket *>(obj)!=NULL;
}

const char *LeachRoutingJoinPacketDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int LeachRoutingJoinPacketDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int LeachRoutingJoinPacketDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *LeachRoutingJoinPacketDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "priorityLevel",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int LeachRoutingJoinPacketDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='p' && strcmp(fieldName, "priorityLevel")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *LeachRoutingJoinPacketDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *LeachRoutingJoinPacketDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int LeachRoutingJoinPacketDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    LeachRoutingJoinPacket *pp = (LeachRoutingJoinPacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string LeachRoutingJoinPacketDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    LeachRoutingJoinPacket *pp = (LeachRoutingJoinPacket *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getPriorityLevel());
        default: return "";
    }
}

bool LeachRoutingJoinPacketDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    LeachRoutingJoinPacket *pp = (LeachRoutingJoinPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setPriorityLevel(string2long(value)); return true;
        default: return false;
    }
}

const char *LeachRoutingJoinPacketDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    };
}

void *LeachRoutingJoinPacketDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    LeachRoutingJoinPacket *pp = (LeachRoutingJoinPacket *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(LeachRoutingTDMAPacket);

LeachRoutingTDMAPacket::LeachRoutingTDMAPacket(const char *name, int kind) : ::LeachRoutingPacket(name,kind)
{
    schedule_arraysize = 0;
    this->schedule_var = 0;
}

LeachRoutingTDMAPacket::LeachRoutingTDMAPacket(const LeachRoutingTDMAPacket& other) : ::LeachRoutingPacket(other)
{
    schedule_arraysize = 0;
    this->schedule_var = 0;
    copy(other);
}

LeachRoutingTDMAPacket::~LeachRoutingTDMAPacket()
{
    delete [] schedule_var;
}

LeachRoutingTDMAPacket& LeachRoutingTDMAPacket::operator=(const LeachRoutingTDMAPacket& other)
{
    if (this==&other) return *this;
    ::LeachRoutingPacket::operator=(other);
    copy(other);
    return *this;
}

void LeachRoutingTDMAPacket::copy(const LeachRoutingTDMAPacket& other)
{
    delete [] this->schedule_var;
    this->schedule_var = (other.schedule_arraysize==0) ? NULL : new int[other.schedule_arraysize];
    schedule_arraysize = other.schedule_arraysize;
    for (unsigned int i=0; i<schedule_arraysize; i++)
        this->schedule_var[i] = other.schedule_var[i];
}

void LeachRoutingTDMAPacket::parsimPack(cCommBuffer *b)
{
    ::LeachRoutingPacket::parsimPack(b);
    b->pack(schedule_arraysize);
    doPacking(b,this->schedule_var,schedule_arraysize);
}

void LeachRoutingTDMAPacket::parsimUnpack(cCommBuffer *b)
{
    ::LeachRoutingPacket::parsimUnpack(b);
    delete [] this->schedule_var;
    b->unpack(schedule_arraysize);
    if (schedule_arraysize==0) {
        this->schedule_var = 0;
    } else {
        this->schedule_var = new int[schedule_arraysize];
        doUnpacking(b,this->schedule_var,schedule_arraysize);
    }
}

void LeachRoutingTDMAPacket::setScheduleArraySize(unsigned int size)
{
    int *schedule_var2 = (size==0) ? NULL : new int[size];
    unsigned int sz = schedule_arraysize < size ? schedule_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        schedule_var2[i] = this->schedule_var[i];
    for (unsigned int i=sz; i<size; i++)
        schedule_var2[i] = 0;
    schedule_arraysize = size;
    delete [] this->schedule_var;
    this->schedule_var = schedule_var2;
}

unsigned int LeachRoutingTDMAPacket::getScheduleArraySize() const
{
    return schedule_arraysize;
}

int LeachRoutingTDMAPacket::getSchedule(unsigned int k) const
{
    if (k>=schedule_arraysize) throw cRuntimeError("Array of size %d indexed by %d", schedule_arraysize, k);
    return schedule_var[k];
}

void LeachRoutingTDMAPacket::setSchedule(unsigned int k, int schedule)
{
    if (k>=schedule_arraysize) throw cRuntimeError("Array of size %d indexed by %d", schedule_arraysize, k);
    this->schedule_var[k] = schedule;
}

class LeachRoutingTDMAPacketDescriptor : public cClassDescriptor
{
  public:
    LeachRoutingTDMAPacketDescriptor();
    virtual ~LeachRoutingTDMAPacketDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(LeachRoutingTDMAPacketDescriptor);

LeachRoutingTDMAPacketDescriptor::LeachRoutingTDMAPacketDescriptor() : cClassDescriptor("LeachRoutingTDMAPacket", "LeachRoutingPacket")
{
}

LeachRoutingTDMAPacketDescriptor::~LeachRoutingTDMAPacketDescriptor()
{
}

bool LeachRoutingTDMAPacketDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<LeachRoutingTDMAPacket *>(obj)!=NULL;
}

const char *LeachRoutingTDMAPacketDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int LeachRoutingTDMAPacketDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int LeachRoutingTDMAPacketDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *LeachRoutingTDMAPacketDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "schedule",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int LeachRoutingTDMAPacketDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "schedule")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *LeachRoutingTDMAPacketDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *LeachRoutingTDMAPacketDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int LeachRoutingTDMAPacketDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    LeachRoutingTDMAPacket *pp = (LeachRoutingTDMAPacket *)object; (void)pp;
    switch (field) {
        case 0: return pp->getScheduleArraySize();
        default: return 0;
    }
}

std::string LeachRoutingTDMAPacketDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    LeachRoutingTDMAPacket *pp = (LeachRoutingTDMAPacket *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getSchedule(i));
        default: return "";
    }
}

bool LeachRoutingTDMAPacketDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    LeachRoutingTDMAPacket *pp = (LeachRoutingTDMAPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setSchedule(i,string2long(value)); return true;
        default: return false;
    }
}

const char *LeachRoutingTDMAPacketDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    };
}

void *LeachRoutingTDMAPacketDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    LeachRoutingTDMAPacket *pp = (LeachRoutingTDMAPacket *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(LeachRoutingDataAggregatedPacket);

LeachRoutingDataAggregatedPacket::LeachRoutingDataAggregatedPacket(const char *name, int kind) : ::LeachRoutingPacket(name,kind)
{
    indivSources_arraysize = 0;
    this->indivSources_var = 0;
    indivSeqNum_arraysize = 0;
    this->indivSeqNum_var = 0;
    indivCreationTimestamp_arraysize = 0;
    this->indivCreationTimestamp_var = 0;
}

LeachRoutingDataAggregatedPacket::LeachRoutingDataAggregatedPacket(const LeachRoutingDataAggregatedPacket& other) : ::LeachRoutingPacket(other)
{
    indivSources_arraysize = 0;
    this->indivSources_var = 0;
    indivSeqNum_arraysize = 0;
    this->indivSeqNum_var = 0;
    indivCreationTimestamp_arraysize = 0;
    this->indivCreationTimestamp_var = 0;
    copy(other);
}

LeachRoutingDataAggregatedPacket::~LeachRoutingDataAggregatedPacket()
{
    delete [] indivSources_var;
    delete [] indivSeqNum_var;
    delete [] indivCreationTimestamp_var;
}

LeachRoutingDataAggregatedPacket& LeachRoutingDataAggregatedPacket::operator=(const LeachRoutingDataAggregatedPacket& other)
{
    if (this==&other) return *this;
    ::LeachRoutingPacket::operator=(other);
    copy(other);
    return *this;
}

void LeachRoutingDataAggregatedPacket::copy(const LeachRoutingDataAggregatedPacket& other)
{
    delete [] this->indivSources_var;
    this->indivSources_var = (other.indivSources_arraysize==0) ? NULL : new int[other.indivSources_arraysize];
    indivSources_arraysize = other.indivSources_arraysize;
    for (unsigned int i=0; i<indivSources_arraysize; i++)
        this->indivSources_var[i] = other.indivSources_var[i];
    delete [] this->indivSeqNum_var;
    this->indivSeqNum_var = (other.indivSeqNum_arraysize==0) ? NULL : new int[other.indivSeqNum_arraysize];
    indivSeqNum_arraysize = other.indivSeqNum_arraysize;
    for (unsigned int i=0; i<indivSeqNum_arraysize; i++)
        this->indivSeqNum_var[i] = other.indivSeqNum_var[i];
    delete [] this->indivCreationTimestamp_var;
    this->indivCreationTimestamp_var = (other.indivCreationTimestamp_arraysize==0) ? NULL : new simtime_t[other.indivCreationTimestamp_arraysize];
    indivCreationTimestamp_arraysize = other.indivCreationTimestamp_arraysize;
    for (unsigned int i=0; i<indivCreationTimestamp_arraysize; i++)
        this->indivCreationTimestamp_var[i] = other.indivCreationTimestamp_var[i];
}

void LeachRoutingDataAggregatedPacket::parsimPack(cCommBuffer *b)
{
    ::LeachRoutingPacket::parsimPack(b);
    b->pack(indivSources_arraysize);
    doPacking(b,this->indivSources_var,indivSources_arraysize);
    b->pack(indivSeqNum_arraysize);
    doPacking(b,this->indivSeqNum_var,indivSeqNum_arraysize);
    b->pack(indivCreationTimestamp_arraysize);
    doPacking(b,this->indivCreationTimestamp_var,indivCreationTimestamp_arraysize);
}

void LeachRoutingDataAggregatedPacket::parsimUnpack(cCommBuffer *b)
{
    ::LeachRoutingPacket::parsimUnpack(b);
    delete [] this->indivSources_var;
    b->unpack(indivSources_arraysize);
    if (indivSources_arraysize==0) {
        this->indivSources_var = 0;
    } else {
        this->indivSources_var = new int[indivSources_arraysize];
        doUnpacking(b,this->indivSources_var,indivSources_arraysize);
    }
    delete [] this->indivSeqNum_var;
    b->unpack(indivSeqNum_arraysize);
    if (indivSeqNum_arraysize==0) {
        this->indivSeqNum_var = 0;
    } else {
        this->indivSeqNum_var = new int[indivSeqNum_arraysize];
        doUnpacking(b,this->indivSeqNum_var,indivSeqNum_arraysize);
    }
    delete [] this->indivCreationTimestamp_var;
    b->unpack(indivCreationTimestamp_arraysize);
    if (indivCreationTimestamp_arraysize==0) {
        this->indivCreationTimestamp_var = 0;
    } else {
        this->indivCreationTimestamp_var = new simtime_t[indivCreationTimestamp_arraysize];
        doUnpacking(b,this->indivCreationTimestamp_var,indivCreationTimestamp_arraysize);
    }
}

void LeachRoutingDataAggregatedPacket::setIndivSourcesArraySize(unsigned int size)
{
    int *indivSources_var2 = (size==0) ? NULL : new int[size];
    unsigned int sz = indivSources_arraysize < size ? indivSources_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        indivSources_var2[i] = this->indivSources_var[i];
    for (unsigned int i=sz; i<size; i++)
        indivSources_var2[i] = 0;
    indivSources_arraysize = size;
    delete [] this->indivSources_var;
    this->indivSources_var = indivSources_var2;
}

unsigned int LeachRoutingDataAggregatedPacket::getIndivSourcesArraySize() const
{
    return indivSources_arraysize;
}

int LeachRoutingDataAggregatedPacket::getIndivSources(unsigned int k) const
{
    if (k>=indivSources_arraysize) throw cRuntimeError("Array of size %d indexed by %d", indivSources_arraysize, k);
    return indivSources_var[k];
}

void LeachRoutingDataAggregatedPacket::setIndivSources(unsigned int k, int indivSources)
{
    if (k>=indivSources_arraysize) throw cRuntimeError("Array of size %d indexed by %d", indivSources_arraysize, k);
    this->indivSources_var[k] = indivSources;
}

void LeachRoutingDataAggregatedPacket::setIndivSeqNumArraySize(unsigned int size)
{
    int *indivSeqNum_var2 = (size==0) ? NULL : new int[size];
    unsigned int sz = indivSeqNum_arraysize < size ? indivSeqNum_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        indivSeqNum_var2[i] = this->indivSeqNum_var[i];
    for (unsigned int i=sz; i<size; i++)
        indivSeqNum_var2[i] = 0;
    indivSeqNum_arraysize = size;
    delete [] this->indivSeqNum_var;
    this->indivSeqNum_var = indivSeqNum_var2;
}

unsigned int LeachRoutingDataAggregatedPacket::getIndivSeqNumArraySize() const
{
    return indivSeqNum_arraysize;
}

int LeachRoutingDataAggregatedPacket::getIndivSeqNum(unsigned int k) const
{
    if (k>=indivSeqNum_arraysize) throw cRuntimeError("Array of size %d indexed by %d", indivSeqNum_arraysize, k);
    return indivSeqNum_var[k];
}

void LeachRoutingDataAggregatedPacket::setIndivSeqNum(unsigned int k, int indivSeqNum)
{
    if (k>=indivSeqNum_arraysize) throw cRuntimeError("Array of size %d indexed by %d", indivSeqNum_arraysize, k);
    this->indivSeqNum_var[k] = indivSeqNum;
}

void LeachRoutingDataAggregatedPacket::setIndivCreationTimestampArraySize(unsigned int size)
{
    simtime_t *indivCreationTimestamp_var2 = (size==0) ? NULL : new simtime_t[size];
    unsigned int sz = indivCreationTimestamp_arraysize < size ? indivCreationTimestamp_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        indivCreationTimestamp_var2[i] = this->indivCreationTimestamp_var[i];
    for (unsigned int i=sz; i<size; i++)
        indivCreationTimestamp_var2[i] = 0;
    indivCreationTimestamp_arraysize = size;
    delete [] this->indivCreationTimestamp_var;
    this->indivCreationTimestamp_var = indivCreationTimestamp_var2;
}

unsigned int LeachRoutingDataAggregatedPacket::getIndivCreationTimestampArraySize() const
{
    return indivCreationTimestamp_arraysize;
}

simtime_t LeachRoutingDataAggregatedPacket::getIndivCreationTimestamp(unsigned int k) const
{
    if (k>=indivCreationTimestamp_arraysize) throw cRuntimeError("Array of size %d indexed by %d", indivCreationTimestamp_arraysize, k);
    return indivCreationTimestamp_var[k];
}

void LeachRoutingDataAggregatedPacket::setIndivCreationTimestamp(unsigned int k, simtime_t indivCreationTimestamp)
{
    if (k>=indivCreationTimestamp_arraysize) throw cRuntimeError("Array of size %d indexed by %d", indivCreationTimestamp_arraysize, k);
    this->indivCreationTimestamp_var[k] = indivCreationTimestamp;
}

class LeachRoutingDataAggregatedPacketDescriptor : public cClassDescriptor
{
  public:
    LeachRoutingDataAggregatedPacketDescriptor();
    virtual ~LeachRoutingDataAggregatedPacketDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(LeachRoutingDataAggregatedPacketDescriptor);

LeachRoutingDataAggregatedPacketDescriptor::LeachRoutingDataAggregatedPacketDescriptor() : cClassDescriptor("LeachRoutingDataAggregatedPacket", "LeachRoutingPacket")
{
}

LeachRoutingDataAggregatedPacketDescriptor::~LeachRoutingDataAggregatedPacketDescriptor()
{
}

bool LeachRoutingDataAggregatedPacketDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<LeachRoutingDataAggregatedPacket *>(obj)!=NULL;
}

const char *LeachRoutingDataAggregatedPacketDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int LeachRoutingDataAggregatedPacketDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int LeachRoutingDataAggregatedPacketDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *LeachRoutingDataAggregatedPacketDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "indivSources",
        "indivSeqNum",
        "indivCreationTimestamp",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int LeachRoutingDataAggregatedPacketDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='i' && strcmp(fieldName, "indivSources")==0) return base+0;
    if (fieldName[0]=='i' && strcmp(fieldName, "indivSeqNum")==0) return base+1;
    if (fieldName[0]=='i' && strcmp(fieldName, "indivCreationTimestamp")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *LeachRoutingDataAggregatedPacketDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "simtime_t",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *LeachRoutingDataAggregatedPacketDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int LeachRoutingDataAggregatedPacketDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    LeachRoutingDataAggregatedPacket *pp = (LeachRoutingDataAggregatedPacket *)object; (void)pp;
    switch (field) {
        case 0: return pp->getIndivSourcesArraySize();
        case 1: return pp->getIndivSeqNumArraySize();
        case 2: return pp->getIndivCreationTimestampArraySize();
        default: return 0;
    }
}

std::string LeachRoutingDataAggregatedPacketDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    LeachRoutingDataAggregatedPacket *pp = (LeachRoutingDataAggregatedPacket *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getIndivSources(i));
        case 1: return long2string(pp->getIndivSeqNum(i));
        case 2: return double2string(pp->getIndivCreationTimestamp(i));
        default: return "";
    }
}

bool LeachRoutingDataAggregatedPacketDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    LeachRoutingDataAggregatedPacket *pp = (LeachRoutingDataAggregatedPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setIndivSources(i,string2long(value)); return true;
        case 1: pp->setIndivSeqNum(i,string2long(value)); return true;
        case 2: pp->setIndivCreationTimestamp(i,string2double(value)); return true;
        default: return false;
    }
}

const char *LeachRoutingDataAggregatedPacketDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    };
}

void *LeachRoutingDataAggregatedPacketDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    LeachRoutingDataAggregatedPacket *pp = (LeachRoutingDataAggregatedPacket *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


