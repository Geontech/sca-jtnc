
/*{% block license %}*/
/*# Allow child templates to include license #*/
/*{% endblock %}*/
//% set includeGuard = component.name.upper().replace('.','') + '_ENTRY_POINTS_H'
//% set executeClass = "Resource_impl" if component.executesHWComponents else "Device_impl"
#ifndef ${includeGuard}
#define ${includeGuard}

// ************* AGREED UPON METHOD TO INSTANTIATE DEVICE FROM SHARED OBJECT *************
//
//   The following typedef defines how the shared object should be constructed.  Any
//   additional parameters may be passed in as long as each persona device supports the
//   construct method signature.  Any updates to the ConstructorPtr typedef requires a
//   change to the 'generateResource' method to pass in the additional parameters
//   defined in the 'ConstructorPtr' typedef.
//
//     IE: If a specific api/interface object is to be shared with each persona device,
//         the following changes are required
//
//          Within this entry point file:
//          typedef ${executeClass}* (*ConstructorPtr)(int, char*[], SharedAPIObjectType*)
//
//          Within 'generatePersona' method located in the resource cpp file:
//          ${executeClass}* personaPtr = personaEntryPoint(argc, argv, SharedAPIObject);
//
typedef ${executeClass}* (*ConstructorPtr)(int, char*[], Device_impl* parentDevice);

#endif // ${includeGuard}
