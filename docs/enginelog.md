# Engine evolution

Engine architectural decisions, problems. Used as a development diary to look back later on the process.

# Unsubscribe all
2025-02-02

Client can unsubscribe from all the messages they subscribed with a single function call. The solution required storing the subscribed message types per subscribed objects. This way the code can easily find the subscriptions that are stored by the reverse order mapping.

# Subscription without inheritence
2025-02-01

### Problem
- Only those classes can subscribe to messages that implement the **recipient\<T\>** interface.
- This can result in multiple inheritence of the same interface by only differring in the message type template parameter. This started to grow in **app** class.
- It would be more convinient to eliminate the usage of inheritence.
- Eliminating the inheritance would also mean a more simpler method for implementing unsubscribing from all the messages.

### Solution
- Passing the message handler **method's pointer** to the **subscribe** function instead of a reference to an object that implements **recipient\<T\>** interface. These two pointers must be bound to a single function call, because the **send** method have no information about the recipient's type and thus can't cast it to pass to the handler with the message.
- **send** function must call the abstract handler function but can't execute the handler with a message type templated call. This is be cause the container can't store multiple types and every template definition of the stored type must be complete. So the **send** function must call the abstract handler with a **generic message type and pass it by address**. Because of this passes the message as a **void pointer**.
- Because of this the casting of the message's type must occur in a place where it's known. This place is the **subscribe** method. It knows the type of the message, recipient and handler member function. The abstract handler's definition contains the **reinterpret cast** from void pointer to the **message's type pointer**.

# Imported engine code from snake project
2025-02-01

Imported basic engine classes from the snake project because this engine will use the same Entity Component System architecture and considered an evolution of the previous engine. The concepts are similar but in some cases it favours modules instead of classes.

# SDL2 lib referencing
2025-01-31

There is no seperate **lib/<library_name>/include** directory because dependencies managed entirely by CMake configuration. Only the SDL_image header copied to the SDL2 dependency's include directory because it references SDL2 header.

# glm library usage
2025-01-31

glm library used instead of the custom vector2 implementation because the engine will support OpenGL in the future and it's GLSL language. glm library is designed to seamlessly integrate with OpenGL and it's also a fast and reliable library. 

# Modularization instead of singleton
2025-01-31

Refactored some engine related singleton classes to modules because but they are truly modules. No need for class definitions because there is no plan to load multiple app instances by a parent process that manages their lifetimes. Only one engine instance runs per app instances.
- logger
- messenger
- scene_loader
- rendering_engine
- gameplay_engine
- collision_engine

