# Architecture 
*App.cpp* would run the game loop and handle the main game logic.

It would also manage the **Game State**, pausing, stooping, and restarting the game.

Calling **HandleInput** & Other Function is also it's responsibility.

``` cpp
if (const auto ecode = Window::ProcessMessages())
{
    return *ecode;
}
```
INSTEAD OF THAT, DOING THIS
```cpp
if (const std::optional<int> ecode = Window::ProcessMessages())
{
    return *ecode;
}
```

### WRONG
```cpp
namespace SiaRift
{
	
}

class Window :
	public Base
{
};
```

### CORRECT 
```cpp
namespace SiaRift
{
	
}

class Window :
	public SiaRift::Base
{
};```

```cpp
namespace SiaRift
{
	class Window :
	public Base
	{
	};
}

```

# Window Class 
```
Program starts
↓
First Window created → Constructor of Window called
↓
WindowClass::GetName() called inside Window constructor
↓
Triggers construction of static WindowClass::wndClass
↓
→ Calls WindowClass::WindowClass()
   → Registers Win32 class with RegisterClassEx()
↓
CreateWindow() creates the actual window
↓
Program continues
```

1. What if you named your file Windows.h?
-	Problem: If you name your own file Windows.h, it can conflict with the system header <Windows.h>.
-	Result: The compiler might include your file instead of the real Windows API header, causing errors like missing types (HWND, etc.).
-	Best Practice: Avoid naming your files the same as standard or system headers.
2. Where does <Windows.h> come from?
-	Source: <Windows.h> is part of the Windows SDK, which provides the Windows API for C++ development.
-	Location: It’s typically stored in a directory like C:\Program Files (x86)\Windows Kits\10\Include\... on your system.
3. Do you need to download it?
-	If you use Visual Studio: The Windows SDK is usually installed automatically with Visual Studio.
-	If not installed: You can add it via the Visual Studio Installer or download the Windows SDK separately from Microsoft.
4. How does the compiler find it?
-	Include Paths: Visual Studio sets up include paths to point to the Windows SDK directories, so #include <Windows.h> works out of the box.
-	Don’t name your files the same as system headers.
-	<Windows.h> comes from the Windows SDK, which is pre-installed with Visual Studio or can be added.
-	The compiler finds it using configured include paths.
Let me know if you want to see how to check or change your include directories in Visual Studio!

# Question - You don't explicitly assign anything to `Window::WindowClass::wndClass` in the .cpp file, and you don't directly call `Window::WindowClass::wndClass.someMethod();` anywhere to trigger it.
In C++, that line Window::WindowClass Window::WindowClass::wndClass; is not just a declaration. For a static (or global) object of a user-defined type like WindowClass, this line is the definition of that object, and as part of its definition, it triggers the automatic call to its default constructor.




# Question If there are multiple window object doesnt that mean `Window::WindowClass Window::WindowClass::wndClass` in .cpp get calling multiple times??
==**CRUX SOLUTION: look even if there's no object of that class, you should be able to access Static stuff from class itself.**==

**Don't you think that implies at something? ==that static variable ain't stored inside an specific object==**

==so question is where it is stored? answer you will create memory for it once and assign it!!!!==

- Static = only one (whether class static or static local)
- Constructor = per object
- Function body = per call
Great question! Here's the difference:

## The Key Difference:

### `int MyClass::ball = 9;` ✅ **DEFINITION**
- **Creates** the memory for the static variable
- **Must be done exactly once** in your program
- The `int` tells the compiler "allocate storage for this"
- This is what goes in your `.cpp` file

### `MyClass::ball = 9;` ❌ **ASSIGNMENT** 
- **Assigns** to existing memory
- **Only works if** `ball` was already defined somewhere
- No `int` because we're not creating storage
- This would work AFTER the variable exists

### `ball = 9;` ❌ **WRONG VARIABLE**
- Assigns to some variable named `ball` in current scope
- **Not** the class member `MyClass::ball`
- Completely different variable

## Think of it like this:

1. **Header**: "I promise there's a static variable called `ball`"
2. **Definition**: "Here it is! Create it and set it to 9" ← `int MyClass::ball = 9;`
3. **Later assignment**: "Change the existing `ball` to something else" ← `MyClass::ball = 999;`

You **must** have the definition step before you can do assignments. That's why you need the `int` the first time!

**Exactly!** You've got it! 🎯

## Static Members vs Instance Members

### **Static Members** (`static int ball;`)
- **Header (.h)**: Just a **promise** - "this will exist somewhere"
- **No memory allocated** until you write the definition in .cpp
- **Must be explicitly defined** with `int MyClass::ball = 9;`
- **Without definition**: Linker error - "undefined reference"

### **Instance Members** (`int apple;`, `int cat;`)
- **Header (.h)**: Also just a blueprint
- **Memory allocated** when you create an object (`MyClass obj;`)
- **No separate definition needed** - memory comes automatically with each object

## Summary:

**Header files (.h)** are just **blueprints/promises** - no actual memory!

**Memory allocation happens:**
- **Static members**: When you write the definition (`int MyClass::ball = 9;`)
- **Instance members**: When you create objects (`MyClass obj;`)

**If you forget the static definition**, you get a **linker error** when you try to use it, because the compiler can't find the actual memory location.

Think of it like architectural blueprints vs actually building the house - the blueprint shows rooms, but no actual rooms exist until construction!

### Why your C# brain is confused:
In C#, you're used to writing static int ball = 9; and it "just works." In C++, that's only half the job - you've declared it exists, but haven't actually created the memory storage yet!


## 🧾 Your Code Summary

### `MyClass.h`


```cpp
// MyClass.h
class MyClass {
public:
    int apple;
    static int ball;
    int cat;
};
```

### `MyClass.cpp`

```cpp
int apple{5};
int ball{7};
int cat{8};
```
### Reality

```cpp
// MyClass.cpp
int MyClass::ball = 7;     // Define and initialize static member
// apple and cat are *not* defined here like this!
// Each object will initialize their own in the constructor or elsewhere
```
```cpp
// WRONG WAYS (commented out):
/*
// ❌ WRONG - these are not inside any function/constructor:
apple = 5;        // ERROR: apple needs an object instance
int ball = 9;     // ERROR: redefinition, should be "int MyClass::ball = 9;"
cat = 8;          // ERROR: cat needs an object instance
*/
```
---

## 🔍 What Happens on Object Creation?

Say you do this in `main.cpp`:

```cpp
MyClass obj1;
MyClass obj2;
```

---

### Here's What Happens:

| Member  | Static? | Initialized Where?                  | Called per Object?      | Notes                        |
| ------- | ------- | ----------------------------------- | ----------------------- | ---------------------------- |
| `apple` | ❌ No    | Per-object (not in `.cpp`)          | ✅ Yes (once per object) | Each object has its own copy |
| `ball`  | ✅ Yes   | In `.cpp`: `int MyClass::ball = 7;` | ❌ No (only once)        | Shared by all objects        |
| `cat`   | ❌ No    | Per-object (not in `.cpp`)          | ✅ Yes (once per object) | Each object has its own copy |

---

## 🧠 In Simple Words:

* `apple` and `cat` are **normal variables** — every `MyClass` object gets its **own**.
* `ball` is `static` — only **one copy** exists for the **entire class**, no matter how many objects you create.
* The `.cpp` file gives `ball` its one-and-only actual storage location and value.
* `apple` and `cat` should be initialized via constructor or defaults — **not in the `.cpp` file** like you wrote.

---

## ❗ Correction Needed for `.cpp`

You can't do this for non-static members:

```cpp
apple{5}; // ❌ invalid outside a constructor or object
cat{8};   // ❌ same issue
```

Instead, use the constructor or in-class initialization:

```cpp
class MyClass {
public:
    int apple = 5;
    static int ball;
    int cat = 8;
};
```

OR in the constructor:

```cpp
MyClass::MyClass() : apple(5), cat(8) {}
```

---

### ✅ Final Notes

* Static members: `ball` — **shared**, **defined once** in `.cpp`
* Non-static: `apple`, `cat` — **unique per object**, **initialized per object**
* Only `ball` gets set once — `apple` and `cat` set every time a new object is made

Let me know if you want a full runnable example with print statements to observe this behavior live.






# Question - what if say it was like static int a{5}; in .h file, do i still need `cpp`, will it say error multi definition or something?

### ❓What if you wrote this in a header?

```cpp
// In .h
class MyClass {
public:
    static int a{5};
};
```

What happens **depends on the version of C++ you're using**.

---

## 🧓 Before C++17 (C++11, C++14):

You can **declare** it like that in the header:

```cpp
static int a; // or even static int a{5};
```

But you MUST still define it **in a .cpp file**:

```cpp
// In .cpp
int MyClass::a = 5;
```

Otherwise, the linker says: ❌ “I can’t find the definition of `a`.”

---

## 🆕 C++17 and later:

Now, you can do this:

```cpp
// In .h
class MyClass {
public:
    inline static int a{5};  // ✅ No .cpp needed
};
```

Using `inline static` **both declares and defines** the variable. No `.cpp` definition is required.

> 🔑 `inline` means: “This definition can appear in multiple translation units, and that's OK.”

---

### ⚠️ But if you write `static int a{5};` **without** `inline`, even in C++17...

You’re declaring `a`, but you’re not defining it. So the compiler will say:

```
error: undefined reference to 'MyClass::a'
```

unless you still define it in a `.cpp`.

---

## ✅ TL;DR: What happens with `static int a{5};` in .h?

|C++ Version|What happens with `static int a{5};` in `.h`|Need `.cpp` definition?|
|---|---|---|
|C++14 or earlier|It's a declaration only|✅ Yes|
|C++17+|Still just a declaration unless you add `inline`|✅ Yes (unless you use `inline`)|
|C++17+ with `inline static int a{5};`|Declares and defines it|❌ No|

---

Let me know your compiler or standard (e.g. MSVC, GCC, using C++17 or 20?), and I can tailor the advice more closely to your setup.
### 🧠 Key C++ Rule:
> A **static data member** of a class must be **declared** inside the class, but also must be **defined** once **outside** the class (typically in a `.cpp` file), unless it's `inline` (C++17+).

### 🛠 Breakdown of What’s Happening
#### **In the `.h` file:**
You're declaring the existence of a static member:

```cpp
class WindowClass {
public:
    static WindowClass wndClass; // <-- This says "This member exists."
};
```
But this is only a **declaration**. It **doesn’t allocate memory** for `wndClass`.

---
#### **In the `.cpp` file:**

You're now actually **defining** it:

```cpp
Window::WindowClass Window::WindowClass::wndClass;
```

This creates the object (just **once**) so the linker can find it when any other code refers to `WindowClass::wndClass`.

---

### 🤔 Why not just define it in the `.h` file?

Because if you include that `.h` in multiple `.cpp` files (which you usually do), you’d get **multiple definitions** of `wndClass`, and that would cause a **linker error** like:

```
LNK2005: 'Window::WindowClass Window::WindowClass::wndClass' already defined in ...
```

So the header only **declares** it, and one `.cpp` file **defines** it.

---

### 🧪 Analogy: Blueprint vs. Actual Object

Imagine a header file like a **blueprint**:

- 🗂 `.h` says: “There will be a **static object** called `wndClass`.”
    
- 🛠 `.cpp` says: “Here it **is**, built and ready to use.”
    

---

### ✅ Summary (Straight Answer)

|File|Code|Meaning|
|---|---|---|
|`.h`|`static WindowClass wndClass;`|Declares the static member|
|`.cpp`|`Window::WindowClass Window::WindowClass::wndClass;`|Defines (instantiates) the static member|

Without the `.cpp` line, there's no actual object created. The compiler knows it _should exist_, but the linker can’t find it.

---

Let me know if you'd like me to visualize this with a simple minimal example in code or memory layout—it can help a lot.