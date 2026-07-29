
using System.Runtime.InteropServices;

[DllImport("core.dll", CallingConvention = CallingConvention.Cdecl)]
static extern int core_abi_version();

[DllImport("core.dll", CallingConvention = CallingConvention.Cdecl)]
static extern int core_add(int a, int b);

Console.WriteLine(core_abi_version());
Console.WriteLine(core_add(1, 5));
