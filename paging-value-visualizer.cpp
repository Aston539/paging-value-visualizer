#define _CRT_SECURE_NO_WARNINGS

#include <cstdint>
#include <cstdio>

#include <wtypes.h>

#define PAGING_VISUALIZER_VALUE_TYPE_PTE 1
#define PAGING_VISUALIZER_VALUE_TYPE_NESTED_PTE 2
#define PAGING_VISUALIZER_VALUE_TYPE_EXTENDED_PTE 3
#define PAGING_VISUALIZER_VALUE_TYPE_VIRTUAL_ADDRESS 4
#define PAGING_VISUALIZER_VALUE_TYPE_PHYSICAL_ADDRESS 5
#define PAGING_VISUALIZER_VALUE_TYPE_PAGING_BASE_DESCRIPTOR 6
#define PAGING_VISUALIZER_VALUE_TYPE_RFLAGS 7
#define PAGING_VISUALIZER_VALUE_TYPE_NPT_EXITINFO 8

typedef union _MM_VIRTUAL_ADDRESS
{
    ULONG64 Value;

    struct
    {
        ULONG64 Offset    : 12;
        ULONG64 PTIndex   : 9;
        ULONG64 PDIndex   : 9;
        ULONG64 PDPTIndex : 9;
        ULONG64 PML4Index : 9;
        ULONG64 Reserved  : 16;
    };

    struct
    {
        ULONG64 Offset    : 21;
        ULONG64 PDIndex   : 9;
        ULONG64 PDPTIndex : 9;
        ULONG64 PML4Index : 9;
        ULONG64 Reserved  : 16;

    } Large;

    struct
    {
        ULONG64 Offset    : 30;
        ULONG64 PDPTIndex : 9;
        ULONG64 PML4Index : 9;
        ULONG64 Reserved  : 16;

    } Huge;

} MM_VIRTUAL_ADDRESS, * PMM_VIRTUAL_ADDRESS;

static_assert( sizeof( MM_VIRTUAL_ADDRESS ) == sizeof( ULONG64 ), "MM_VIRTUAL_ADDRESS Must be 8 bytes in size" );

typedef union _MM_PHYSICAL_ADDRESS
{
    ULONG64 Value;

    struct
    {
        ULONG64 Offset : 12;
    };

} MM_PHYSICAL_ADDRESS, * PMM_PHYSICAL_ADDRESS;

static_assert( sizeof( MM_PHYSICAL_ADDRESS ) == sizeof( ULONG64 ), "MM_PHYSICAL_ADDRESS Must be 8 bytes in size" );

typedef union _MM_PTE_DESCRIPTOR
{
    ULONG64 Value;

    //
    // Intel SDM Volume 3
    // Table 5-20. Format of a Page-Table Entry that Maps a 4-KByte Page
    //
    struct
    {
        ULONG64 Present          : 1;   // [0]
        ULONG64 Writable         : 1;   // [1]
        ULONG64 UserSupervisor   : 1;   // [2]
        ULONG64 PageWriteThrough : 1;   // [3]
        ULONG64 PageCacheDisable : 1;   // [4]
        ULONG64 Accessed         : 1;   // [5]
        ULONG64 Dirty            : 1;   // [6]
        ULONG64 PAT              : 1;   // [7]
        ULONG64 Global           : 1;   // [8]
        ULONG64 Ignored1         : 2;   // [10:9]
        ULONG64 HLATRestart      : 1;   // [11]
        ULONG64 PageFrameNumber  : 36;  // [47:12]
        ULONG64 Reserved0        : 4;   // [51:48]
        ULONG64 Ignored2         : 7;   // [58:52]
        ULONG64 ProtectionKey    : 4;   // [62:59]
        ULONG64 NoExecute        : 1;   // [63]
    };

    //
    // Intel SDM Volume 3
    // Table 5-18. Format of a Page-Directory Entry that Maps a 2-MByte Page
    //
    struct
    {
        ULONG64 Present          : 1;   // [0]
        ULONG64 Writable         : 1;   // [1]
        ULONG64 UserSupervisor   : 1;   // [2]
        ULONG64 PageWriteThrough : 1;   // [3]
        ULONG64 PageCacheDisable : 1;   // [4]
        ULONG64 Accessed         : 1;   // [5]
        ULONG64 Dirty            : 1;   // [6]
        ULONG64 LargePage        : 1;   // [7]
        ULONG64 Global           : 1;   // [8]
        ULONG64 Ignored1         : 2;   // [10:9]
        ULONG64 HLATRestart      : 1;   // [11]
        ULONG64 PAT              : 1;   // [12]
        ULONG64 Reserved0        : 8;   // [20:13]
        ULONG64 PageFrameNumber  : 31;  // [51:21]
        ULONG64 Reserved1        : 1;   // [52]
        ULONG64 Ignored2         : 6;   // [58:53]
        ULONG64 ProtectionKey    : 4;   // [62:59]
        ULONG64 NoExecute        : 1;   // [63]

    } Large;

    //
    // Intel SDM Volume 3
    // Table 5-16. Format of a Page-Directory-Pointer-Table Entry (PDPTE) that Maps a 1-GByte Page
    //
    struct
    {
        ULONG64 Present          : 1;   // [0]
        ULONG64 Writable         : 1;   // [1]
        ULONG64 UserSupervisor   : 1;   // [2]
        ULONG64 PageWriteThrough : 1;   // [3]
        ULONG64 PageCacheDisable : 1;   // [4]
        ULONG64 Accessed         : 1;   // [5]
        ULONG64 Dirty            : 1;   // [6]
        ULONG64 LargePage        : 1;   // [7]
        ULONG64 Global           : 1;   // [8]
        ULONG64 Ignored1         : 2;   // [10:9]
        ULONG64 HLATRestart      : 1;   // [11]
        ULONG64 PAT              : 1;   // [12]
        ULONG64 Reserved0        : 17;  // [29:13]
        ULONG64 PageFrameNumber  : 22;  // [51:30]
        ULONG64 Reserved1        : 1;   // [52]
        ULONG64 Ignored2         : 6;   // [58:53]
        ULONG64 ProtectionKey    : 4;   // [62:59]
        ULONG64 NoExecute        : 1;   // [63]

    } Huge;

    union
    {
        struct
        {
            ULONG64 Readable        : 1;   // [0]
            ULONG64 Writable        : 1;   // [1]
            ULONG64 Executable      : 1;   // [2]
            ULONG64 MemoryType      : 3;   // [5:3]
            ULONG64 IgnorePAT       : 1;   // [6]
            ULONG64 Reserved0       : 1;   // [7]
            ULONG64 Accessed        : 1;   // [8]
            ULONG64 Dirty           : 1;   // [9]
            ULONG64 UserExecute     : 1;   // [10]
            ULONG64 Reserved1       : 1;   // [11]
            ULONG64 PageFrameNumber : 36;  // [47:12]
            ULONG64 Reserved2       : 15;  // [62:48]
            ULONG64 SupressVE       : 1;   // [63]
        };

        struct
        {
            ULONG64 Readable        : 1;   // [0]
            ULONG64 Writable        : 1;   // [1]
            ULONG64 Executable      : 1;   // [2]
            ULONG64 MemoryType      : 3;   // [5:3]
            ULONG64 IgnorePAT       : 1;   // [6]
            ULONG64 LargePage       : 1;   // [7]
            ULONG64 Accessed        : 1;   // [8]
            ULONG64 Dirty           : 1;   // [9]
            ULONG64 UserExecute     : 1;   // [10]
            ULONG64 Reserved1       : 10;  // [20:11]
            ULONG64 PageFrameNumber : 27;  // [47:21]
            ULONG64 Reserved2       : 15;  // [62:48]
            ULONG64 SupressVE       : 1;   // [63]

        } Large;

        struct
        {
            ULONG64 Readable        : 1;   // [0]
            ULONG64 Writable        : 1;   // [1]
            ULONG64 Executable      : 1;   // [2]
            ULONG64 MemoryType      : 3;   // [5:3]
            ULONG64 IgnorePAT       : 1;   // [6]
            ULONG64 LargePage       : 1;   // [7]
            ULONG64 Accessed        : 1;   // [8]
            ULONG64 Dirty           : 1;   // [9]
            ULONG64 UserExecute     : 1;   // [10]
            ULONG64 Reserved1       : 19;  // [29:11]
            ULONG64 PageFrameNumber : 18;  // [47:30]
            ULONG64 Reserved2       : 15;  // [62:48]
            ULONG64 SupressVE       : 1;   // [63]

        } Huge;

    } Extended;

} MM_PTE_DESCRIPTOR, * PMM_PTE_DESCRIPTOR;

static_assert( sizeof( MM_PTE_DESCRIPTOR ) == sizeof( ULONG64 ), "MM_PTE_DESCRIPTOR Must be 8 bytes in size" );

typedef union _MM_PAGING_BASE_DESCRIPTOR
{
    ULONG64 Value;

    struct
    {
        ULONG64 Reserved1             : 3;
        ULONG64 PageLevelWriteThrough : 1;
        ULONG64 PageLevelCacheDisable : 1;
        ULONG64 Reserved2             : 7;
        ULONG64 PageFrameNumber       : 36;
        ULONG64 Reserved3             : 16;
    };

} MM_PAGING_BASE_DESCRIPTOR, * PMM_PAGING_BASE_DESCRIPTOR;

static_assert( sizeof( MM_PAGING_BASE_DESCRIPTOR ) == sizeof( ULONG64 ), "MM_PAGING_BASE_DESCRIPTOR Must be 8 bytes" );

typedef union _RFLAGS_REGISTER
{
	ULONG64 Value;

	struct
	{
		ULONG64 CF : 1;  // Carry Flag
		ULONG64 Reserved1 : 1;  // Reserved, always 1
		ULONG64 PF : 1;  // Parity Flag
		ULONG64 Reserved2 : 1;  // Reserved, always 0
		ULONG64 AF : 1;  // Auxiliary Carry Flag
		ULONG64 Reserved3 : 1;  // Reserved, always 0
		ULONG64 ZF : 1;  // Zero Flag
		ULONG64 SF : 1;  // Sign Flag
		ULONG64 TF : 1;  // Trap Flag (single-step)
		ULONG64 IF : 1;  // Interrupt Enable Flag
		ULONG64 DF : 1;  // Direction Flag
		ULONG64 OF : 1;  // Overflow Flag
		ULONG64 IOPL : 2;  // I/O Privilege Level
		ULONG64 NT : 1;  // Nested Task
		ULONG64 Reserved4 : 1;  // Reserved
		ULONG64 RF : 1;  // Resume Flag
		ULONG64 VM : 1;  // Virtual-8086 Mode
		ULONG64 AC : 1;  // Alignment Check
		ULONG64 VIF : 1;  // Virtual Interrupt Flag
		ULONG64 VIP : 1;  // Virtual Interrupt Pending
		ULONG64 ID : 1;  // ID flag (for CPUID)
		ULONG64 Reserved5 : 42; // Reserved
	};

#ifdef __cplusplus
	FORCEINLINE operator ULONG64( ) const
	{
		return Value;
	}

	FORCEINLINE _RFLAGS_REGISTER& operator=( ULONG64 RFlags )
	{
		Value = RFlags;
		return *this;
	}

	FORCEINLINE _RFLAGS_REGISTER( ) : Value( 0 ) { }
	FORCEINLINE _RFLAGS_REGISTER( ULONG64 RFlags ) : Value( RFlags ) { }
#endif

} RFLAGS_REGISTER, * PRFLAGS_REGISTER;

//
// Pacifica:
// 2.21.6 Host Versus Guest Page Faults, Fault Ordering
// Page 81
// 
// AMD64 Architecture Programmers Manual:
// 15.25.6 Nested versus Guest Page Faults, Fault Ordering
// Page 551
//
typedef union _SVM_NPT_EXITINFO1
{
	ULONG64 Value;

	struct
	{
		ULONG64 Valid : 1;                  // [0]
		ULONG64 Write : 1;                  // [1]
		ULONG64 User : 1;                   // [2]
		ULONG64 Reserved : 1;               // [3]
		ULONG64 Execute : 1;                // [4]
		ULONG64 Reserved2 : 1;              // [5]
		ULONG64 ShadowStack : 1;            // [6]
		ULONG64 Reserved3 : 25;             // [5:31]
		ULONG64 GuestPhysicalAddress : 1;   // [32] - 1 if nested page fault occurred while translating the guest’s final physical address
		ULONG64 GuestPageTables : 1;        // [33] - 1 if nested page fault occurred while translating the guest page tables
		ULONG64 Reserved4 : 3;              // [34]
		ULONG64 SupervisorShadowStack : 1;  // [37]
	};

#ifdef __cplusplus
	FORCEINLINE operator ULONG64( )
	{
		return Value;
	}

	FORCEINLINE _SVM_NPT_EXITINFO1& operator=( ULONG64 ExitInfo1 )
	{
		Value = ExitInfo1;
		return *this;
	}

	FORCEINLINE _SVM_NPT_EXITINFO1( VOID ) : Value{ NULL } { }
	FORCEINLINE _SVM_NPT_EXITINFO1( ULONG64 ExitInfo1 ) : Value{ ExitInfo1 } { }
#endif

} SVM_NPT_EXITINFO1, * PSVM_NPT_EXITINFO1;

typedef struct _PAGING_VISUALIZER_INPUT_PARAMETERS
{
	LONG Type;
    ULONG64 Value;

} PAGING_VISUALIZER_INPUT_PARAMETERS, *PPAGING_VISUALIZER_INPUT_PARAMETERS;

LONG
PvsGetPagingTypeFromInput(
	_In_ LPCSTR TypeInput
)
{
	if ( _stricmp( TypeInput, "page-table-entry" ) == 0 || 
         _stricmp( TypeInput, "pte"              ) == 0 )
	{
		return PAGING_VISUALIZER_VALUE_TYPE_PTE;
	}
	else if ( _stricmp( TypeInput, "nested-page-table-entry" ) == 0 || 
              _stricmp( TypeInput, "nested-pte"              ) == 0 ||
			  _stricmp( TypeInput, "npte"                    ) == 0 )
	{
		return PAGING_VISUALIZER_VALUE_TYPE_NESTED_PTE;
	}
	else if ( _stricmp( TypeInput, "extended-page-table-entry" ) == 0 || 
              _stricmp( TypeInput, "extended-pte"              ) == 0 ||
			  _stricmp( TypeInput, "epte"                      ) == 0 )
	{
		return PAGING_VISUALIZER_VALUE_TYPE_EXTENDED_PTE;
	}
	else if ( _stricmp( TypeInput, "virtual-address" ) == 0 ||
			  _stricmp( TypeInput, "virtual"         ) == 0 ||
              _stricmp( TypeInput, "virt"            ) == 0 ||
              _stricmp( TypeInput, "va"              ) == 0 )
	{
		return PAGING_VISUALIZER_VALUE_TYPE_VIRTUAL_ADDRESS;
	}
	else if ( _stricmp( TypeInput, "physical-address" ) == 0 ||
              _stricmp( TypeInput, "physical"         ) == 0 ||
              _stricmp( TypeInput, "phys"             ) == 0 ||
			  _stricmp( TypeInput, "pa"               ) == 0 )
	{
		return PAGING_VISUALIZER_VALUE_TYPE_PHYSICAL_ADDRESS;
	}
    else if ( _stricmp( TypeInput, "paging-base-descriptor" ) == 0 ||
              _stricmp( TypeInput, "paging-base"            ) == 0 ||
              _stricmp( TypeInput, "cr3"                    ) == 0 ||
              _stricmp( TypeInput, "pb"                     ) == 0 )
    {
        return PAGING_VISUALIZER_VALUE_TYPE_PAGING_BASE_DESCRIPTOR;
    }
	else if ( _stricmp( TypeInput, "rflags" ) == 0 ||
		      _stricmp( TypeInput, "eflags" ) == 0 )
	{
		return PAGING_VISUALIZER_VALUE_TYPE_RFLAGS;
	}
	else if ( _stricmp( TypeInput, "nptinfo" ) == 0 )
	{
		return PAGING_VISUALIZER_VALUE_TYPE_NPT_EXITINFO;
	}
    
	return -1;
}

BOOL
PvsInitializeInputParametersFromStringInputs(
    _In_ LPCSTR Type,
    _In_ LPCSTR Value,
    _Inout_ PPAGING_VISUALIZER_INPUT_PARAMETERS InputParameters
)
{
    InputParameters->Type = PvsGetPagingTypeFromInput( Type );
    if ( InputParameters->Type == -1 )
    {
        return FALSE;
    }

    if ( _strnicmp( Value, "0x", 2 ) == 0 )
    {
        InputParameters->Value = strtoull( Value + 2, NULL, 16 );
    }
    else
    {
        InputParameters->Value = strtoull( Value, NULL, 10 );
    }

    if ( errno != 0 )
    {
        return FALSE;
    }

    return TRUE;
}

BOOL
PvsGetInputParametersFromCommandLineArguments(
	_In_ LONG ArgumentCount,
	_In_ LPCSTR* ArgumentArray,
	_Inout_ PPAGING_VISUALIZER_INPUT_PARAMETERS InputParameters
)
{
    if ( ArgumentCount < 2 )
    {
        return FALSE;
    }

    if ( PvsInitializeInputParametersFromStringInputs( ArgumentArray[ 1 ], ArgumentArray[ 2 ], InputParameters ) == FALSE )
    {
        return FALSE;
    }

    return TRUE;
}

BOOL
PvsGetInputParametersFromCommandLine(
	_Inout_ PPAGING_VISUALIZER_INPUT_PARAMETERS InputParameters
)
{
    CHAR VisualizeType[ 32 + 1 ];
    memset( VisualizeType, NULL, sizeof( VisualizeType ) );
    printf( "Enter the type of value you would like to visualize: " );
    if ( scanf( "%32s", VisualizeType ) != 1 )
    {
        return FALSE;
    }

    CHAR VisualizeValue[ 32 + 1 ];
    memset( VisualizeValue, NULL, sizeof( VisualizeValue ) );
    printf( "Enter the value you would like to visualize: " );
    if ( scanf( "%32s", VisualizeValue ) != 1 )
    {
        return FALSE;
    }

    if ( PvsInitializeInputParametersFromStringInputs( VisualizeType, VisualizeValue, InputParameters ) == FALSE )
    {
        return FALSE;
    }

	return TRUE;
}

BOOL
PvsGetInputParameters(
	_In_ LONG ArgumentCount,
	_In_ LPCSTR* ArgumentArray,
	_Inout_ PPAGING_VISUALIZER_INPUT_PARAMETERS InputParameters
)
{
	if ( PvsGetInputParametersFromCommandLineArguments( ArgumentCount, ArgumentArray, InputParameters ) )
	{
        return TRUE;
	}

	return PvsGetInputParametersFromCommandLine( InputParameters );
}

VOID
PvsVisualizeHardwarePTE(
    _In_ ULONG64 Value
)
{
    MM_PTE_DESCRIPTOR HardwarePTE;
    HardwarePTE.Value = Value;

    printf( "Huge:\n" );
    printf( "Huge.Present: %p\n", HardwarePTE.Huge.Present );
    printf( "Huge.Writable: %p\n", HardwarePTE.Huge.Writable );
    printf( "Huge.UserSupervisor: %p\n", HardwarePTE.Huge.UserSupervisor );
    printf( "Huge.PageWriteThrough: %p\n", HardwarePTE.Huge.PageWriteThrough );
    printf( "Huge.PageCacheDisable: %p\n", HardwarePTE.Huge.PageCacheDisable );
    printf( "Huge.Accessed: %p\n", HardwarePTE.Huge.Accessed );
    printf( "Huge.Dirty: %p\n", HardwarePTE.Huge.Dirty );
    printf( "Huge.LargePage: %p\n", HardwarePTE.Huge.LargePage );
    printf( "Huge.Global: %p\n", HardwarePTE.Huge.Global );
    printf( "Huge.Ignored1: %p\n", HardwarePTE.Huge.Ignored1 );
    printf( "Huge.HLATRestart: %p\n", HardwarePTE.Huge.HLATRestart );
    printf( "Huge.PAT: %p\n", HardwarePTE.Huge.PAT );
    printf( "Huge.Reserved0: %p\n", HardwarePTE.Huge.Reserved0 );
    printf( "Huge.PageFrameNumber: %p\n", HardwarePTE.Huge.PageFrameNumber );
    printf( "Huge.Reserved1: %p\n", HardwarePTE.Huge.Reserved1 );
    printf( "Huge.Ignored2: %p\n", HardwarePTE.Huge.Ignored2 );
    printf( "Huge.ProtectionKey: %p\n", HardwarePTE.Huge.ProtectionKey );
    printf( "Huge.NoExecute: %p\n", HardwarePTE.Huge.NoExecute );
    printf( "\n" );

    printf( "Large:\n" );
    printf( "Large.Present: %p\n", HardwarePTE.Large.Present );
    printf( "Large.Writable: %p\n", HardwarePTE.Large.Writable );
    printf( "Large.UserSupervisor: %p\n", HardwarePTE.Large.UserSupervisor );
    printf( "Large.PageWriteThrough: %p\n", HardwarePTE.Large.PageWriteThrough );
    printf( "Large.PageCacheDisable: %p\n", HardwarePTE.Large.PageCacheDisable );
    printf( "Large.Accessed: %p\n", HardwarePTE.Large.Accessed );
    printf( "Large.Dirty: %p\n", HardwarePTE.Large.Dirty );
    printf( "Large.LargePage: %p\n", HardwarePTE.Large.LargePage );
    printf( "Large.Global: %p\n", HardwarePTE.Large.Global );
    printf( "Large.Ignored1: %p\n", HardwarePTE.Large.Ignored1 );
    printf( "Large.HLATRestart: %p\n", HardwarePTE.Large.HLATRestart );
    printf( "Large.PAT: %p\n", HardwarePTE.Large.PAT );
    printf( "Large.Reserved0: %p\n", HardwarePTE.Large.Reserved0 );
    printf( "Large.PageFrameNumber: %p\n", HardwarePTE.Large.PageFrameNumber );
    printf( "Large.Reserved1: %p\n", HardwarePTE.Large.Reserved1 );
    printf( "Large.Ignored2: %p\n", HardwarePTE.Large.Ignored2 );
    printf( "Large.ProtectionKey: %p\n", HardwarePTE.Large.ProtectionKey );
    printf( "Large.NoExecute: %p\n", HardwarePTE.Large.NoExecute );
    printf( "\n" );

    printf( "Small:\n" );
    printf( "Small.Present: %p\n", HardwarePTE.Present );
    printf( "Small.Writable: %p\n", HardwarePTE.Writable );
    printf( "Small.UserSupervisor: %p\n", HardwarePTE.UserSupervisor );
    printf( "Small.PageWriteThrough: %p\n", HardwarePTE.PageWriteThrough );
    printf( "Small.PageCacheDisable: %p\n", HardwarePTE.PageCacheDisable );
    printf( "Small.Accessed: %p\n", HardwarePTE.Accessed );
    printf( "Small.Dirty: %p\n", HardwarePTE.Dirty );
    printf( "Small.PAT: %p\n", HardwarePTE.PAT );
    printf( "Small.Global: %p\n", HardwarePTE.Global );
    printf( "Small.Ignored1: %p\n", HardwarePTE.Ignored1 );
    printf( "Small.HLATRestart: %p\n", HardwarePTE.HLATRestart );
    printf( "Small.PageFrameNumber: %p\n", HardwarePTE.PageFrameNumber );
    printf( "Small.Reserved0: %p\n", HardwarePTE.Reserved0 );
    printf( "Small.Ignored2: %p\n", HardwarePTE.Ignored2 );
    printf( "Small.ProtectionKey: %p\n", HardwarePTE.ProtectionKey );
    printf( "Small.NoExecute: %p\n", HardwarePTE.NoExecute );
    printf( "\n" );
}

VOID
PvsVisualizeExtendedPTE(
    _In_ ULONG64 Value
)
{
    MM_PTE_DESCRIPTOR ExtendedPTE;
    ExtendedPTE.Value = Value;

    printf( "Huge:\n" );
    printf( "Huge.Readable: %p\n", ExtendedPTE.Extended.Huge.Readable );
    printf( "Huge.Writable: %p\n", ExtendedPTE.Extended.Huge.Writable );
    printf( "Huge.Executable: %p\n", ExtendedPTE.Extended.Huge.Executable );
    printf( "Huge.MemoryType: %p\n", ExtendedPTE.Extended.Huge.MemoryType );
    printf( "Huge.IgnorePAT: %p\n", ExtendedPTE.Extended.Huge.IgnorePAT );
    printf( "Huge.LargePage: %p\n", ExtendedPTE.Extended.Huge.LargePage );
    printf( "Huge.Accessed: %p\n", ExtendedPTE.Extended.Huge.Accessed );
    printf( "Huge.Dirty: %p\n", ExtendedPTE.Extended.Huge.Dirty );
    printf( "Huge.UserExecute: %p\n", ExtendedPTE.Extended.Huge.UserExecute );
    printf( "Huge.Reserved1: %p\n", ExtendedPTE.Extended.Huge.Reserved1 );
    printf( "Huge.PageFrameNumber: %p\n", ExtendedPTE.Extended.Huge.PageFrameNumber );
    printf( "Huge.Reserved2: %p\n", ExtendedPTE.Extended.Huge.Reserved2 );
    printf( "Huge.SupressVE: %p\n", ExtendedPTE.Extended.Huge.SupressVE );
    printf( "\n" );

    printf( "Large:\n" );
    printf( "Large.Readable: %p\n", ExtendedPTE.Extended.Large.Readable );
    printf( "Large.Writable: %p\n", ExtendedPTE.Extended.Large.Writable );
    printf( "Large.Executable: %p\n", ExtendedPTE.Extended.Large.Executable );
    printf( "Large.MemoryType: %p\n", ExtendedPTE.Extended.Large.MemoryType );
    printf( "Large.IgnorePAT: %p\n", ExtendedPTE.Extended.Large.IgnorePAT );
    printf( "Large.LargePage: %p\n", ExtendedPTE.Extended.Large.LargePage );
    printf( "Large.Accessed: %p\n", ExtendedPTE.Extended.Large.Accessed );
    printf( "Large.Dirty: %p\n", ExtendedPTE.Extended.Large.Dirty );
    printf( "Large.UserExecute: %p\n", ExtendedPTE.Extended.Large.UserExecute );
    printf( "Large.Reserved1: %p\n", ExtendedPTE.Extended.Large.Reserved1 );
    printf( "Large.PageFrameNumber: %p\n", ExtendedPTE.Extended.Large.PageFrameNumber );
    printf( "Large.Reserved2: %p\n", ExtendedPTE.Extended.Large.Reserved2 );
    printf( "Large.SupressVE: %p\n", ExtendedPTE.Extended.Large.SupressVE );
    printf( "\n" );

    printf( "Small:\n" );
    printf( "Small.Readable: %p\n", ExtendedPTE.Extended.Readable );
    printf( "Small.Writable: %p\n", ExtendedPTE.Extended.Writable );
    printf( "Small.Executable: %p\n", ExtendedPTE.Extended.Executable );
    printf( "Small.MemoryType: %p\n", ExtendedPTE.Extended.MemoryType );
    printf( "Small.IgnorePAT: %p\n", ExtendedPTE.Extended.IgnorePAT );
    printf( "Small.Reserved0: %p\n", ExtendedPTE.Extended.Reserved0 );
    printf( "Small.Accessed: %p\n", ExtendedPTE.Extended.Accessed );
    printf( "Small.Dirty: %p\n", ExtendedPTE.Extended.Dirty );
    printf( "Small.UserExecute: %p\n", ExtendedPTE.Extended.UserExecute );
    printf( "Small.Reserved1: %p\n", ExtendedPTE.Extended.Reserved1 );
    printf( "Small.PageFrameNumber: %p\n", ExtendedPTE.Extended.PageFrameNumber );
    printf( "Small.Reserved2: %p\n", ExtendedPTE.Extended.Reserved2 );
    printf( "Small.SupressVE: %p\n", ExtendedPTE.Extended.SupressVE );
    printf( "\n" );
}

VOID
PvsVisualizeVirtualAddress(
    _In_ ULONG64 Value
)
{
    MM_VIRTUAL_ADDRESS VirtualAddress;
    VirtualAddress.Value = Value;

    printf( "Huge:\n" );
    printf( "Huge.Offset: %p\n", VirtualAddress.Huge.Offset );
    printf( "Huge.PDPTIndex: %p\n", VirtualAddress.Huge.PDPTIndex );
    printf( "Huge.PML4Index: %p\n", VirtualAddress.Huge.PML4Index );
    printf( "Huge.Reserved: %p\n", VirtualAddress.Huge.Reserved );
    printf( "\n" );

    printf( "Large:\n" );
    printf( "Large.Offset: %p\n", VirtualAddress.Large.Offset );
    printf( "Large.PDIndex: %p\n", VirtualAddress.Large.PDIndex );
    printf( "Large.PDPTIndex: %p\n", VirtualAddress.Large.PDPTIndex );
    printf( "Large.PML4Index: %p\n", VirtualAddress.Large.PML4Index );
    printf( "Large.Reserved: %p\n", VirtualAddress.Large.Reserved );
    printf( "\n" );

    printf( "Small:\n" );
    printf( "Small.Offset: %p\n", VirtualAddress.Offset );
    printf( "Small.PTIndex: %p\n", VirtualAddress.PTIndex );
    printf( "Small.PDIndex: %p\n", VirtualAddress.PDIndex );
    printf( "Small.PDPTIndex: %p\n", VirtualAddress.PDPTIndex );
    printf( "Small.PML4Index: %p\n", VirtualAddress.PML4Index );
    printf( "Small.Reserved: %p\n", VirtualAddress.Reserved );
    printf( "\n" );
}

VOID
PvsVisualizePhysicalAddress(
    _In_ ULONG64 Value
)
{
    MM_PHYSICAL_ADDRESS PhysicalAddress;
    PhysicalAddress.Value = Value;

    printf( "Offset: %p\n", PhysicalAddress.Offset );
}

VOID
PvsVisualizePagingBaseDescriptor(
    _In_ ULONG64 Value
)
{
    MM_PAGING_BASE_DESCRIPTOR PagingBaseDescriptor;
    PagingBaseDescriptor.Value = Value;

    printf( "Reserved1: %p\n", PagingBaseDescriptor.Reserved1 );
    printf( "PageLevelWriteThrough: %p\n", PagingBaseDescriptor.PageLevelWriteThrough );
    printf( "PageLevelCacheDisable: %p\n", PagingBaseDescriptor.PageLevelCacheDisable );
    printf( "Reserved2: %p\n", PagingBaseDescriptor.Reserved2 );
    printf( "PageFrameNumber: %p\n", PagingBaseDescriptor.PageFrameNumber );
    printf( "Reserved3: %p\n", PagingBaseDescriptor.Reserved3 );
}

VOID
PvsVisualsizeRFlags(
	_In_ ULONG64 Value
)
{
	RFLAGS_REGISTER RFlags = Value;

	printf( "RFlags.CF: %p\n", RFlags.CF );
	printf( "RFlags.PF: %p\n", RFlags.PF );
	printf( "RFlags.AF: %p\n", RFlags.AF );
	printf( "RFlags.ZF: %p\n", RFlags.ZF );
	printf( "RFlags.SF: %p\n", RFlags.SF );
	printf( "RFlags.TF: %p\n", RFlags.TF );
	printf( "RFlags.IF: %p\n", RFlags.IF );
	printf( "RFlags.DF: %p\n", RFlags.DF );
	printf( "RFlags.OF: %p\n", RFlags.OF );
	printf( "RFlags.IOPL: %p\n", RFlags.IOPL );
	printf( "RFlags.NT: %p\n", RFlags.NT );
	printf( "RFlags.RF: %p\n", RFlags.RF );
	printf( "RFlags.VM: %p\n", RFlags.VM );
	printf( "RFlags.AC: %p\n", RFlags.AC );
	printf( "RFlags.VIF: %p\n", RFlags.VIF );
	printf( "RFlags.VIP: %p\n", RFlags.VIP );
	printf( "RFlags.ID: %p\n", RFlags.ID );
}

VOID
PvsVisualsizeNPTExitInformation(
	_In_ ULONG64 Value
)
{
	SVM_NPT_EXITINFO1 FaultInformation = Value;

	printf( "FaultInformation.Valid	: %p  \n", FaultInformation.Valid );
	printf( "FaultInformation.Write : %p  \n", FaultInformation.Write );
	printf( "FaultInformation.User : %p  \n", FaultInformation.User );
	printf( "FaultInformation.Execute : %p  \n", FaultInformation.Execute );
	printf( "FaultInformation.ShadowStack : %p  \n", FaultInformation.ShadowStack );
	printf( "FaultInformation.GuestPhysicalAddress : %p  \n", FaultInformation.GuestPhysicalAddress );
	printf( "FaultInformation.GuestPageTables : %p  \n", FaultInformation.GuestPageTables );
	printf( "FaultInformation.SupervisorShadowStack : %p  \n", FaultInformation.SupervisorShadowStack );
}

int main(int argc, char** argv)
{
	PAGING_VISUALIZER_INPUT_PARAMETERS InputParameters;
    memset( &InputParameters, NULL, sizeof( PAGING_VISUALIZER_INPUT_PARAMETERS ) );
	if ( PvsGetInputParameters( argc, ( LPCSTR* )argv, &InputParameters ) == FALSE )
	{
		printf( "Invalid usage <Type> <Value>" );

		return 1;
	}

    switch ( InputParameters.Type )
    {
        case PAGING_VISUALIZER_VALUE_TYPE_PTE:
        case PAGING_VISUALIZER_VALUE_TYPE_NESTED_PTE:
        {
            //
            // AMD Nested PTE's are equivelant to standard hardware implementation
            //

            PvsVisualizeHardwarePTE( InputParameters.Value );

        } break;

        case PAGING_VISUALIZER_VALUE_TYPE_EXTENDED_PTE:
        {
            PvsVisualizeExtendedPTE( InputParameters.Value );

        } break;

        case PAGING_VISUALIZER_VALUE_TYPE_VIRTUAL_ADDRESS:
        {
            PvsVisualizeVirtualAddress( InputParameters.Value );

        } break;

        case PAGING_VISUALIZER_VALUE_TYPE_PHYSICAL_ADDRESS:
        {
            PvsVisualizePhysicalAddress( InputParameters.Value );

        } break;

        case PAGING_VISUALIZER_VALUE_TYPE_PAGING_BASE_DESCRIPTOR:
        {
            PvsVisualizePagingBaseDescriptor( InputParameters.Value );

        } break;

		case PAGING_VISUALIZER_VALUE_TYPE_RFLAGS:
		{
			PvsVisualsizeRFlags( InputParameters.Value );

		} break;

		case PAGING_VISUALIZER_VALUE_TYPE_NPT_EXITINFO:
		{
			PvsVisualsizeNPTExitInformation( InputParameters.Value );

		} break;

        default: return 2;
    }

    while ( getchar( ) != 0 )
    {
        Sleep( 50 );
    }

    return 0;
}