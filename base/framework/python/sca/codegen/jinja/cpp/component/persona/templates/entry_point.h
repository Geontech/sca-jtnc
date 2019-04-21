
/*{% block license %}*/
/*# Allow child templates to include license #*/
/*{% endblock %}*/
//% set includeGuard = component.name.upper().replace('.','') + '_ENTRY_POINTS_H'
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
//          Within this header file:
//          typedef void* (*ConstructorPtr)(int, char*[], SharedAPIObject*)
//
//          Within this cpp file:
//          void* personaPtr = construct(argc, argv, SharedAPIObject);
//
typedef ResourceComponent* (*ConstructorPtr)(int, char*[], DeviceComponent* parentDevice);

#endif // ${includeGuard}
