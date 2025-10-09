# paging-value-visualizer

Paging Value Visualizer is a small utility for decoding and visualizing values related to 64bit CPU paging structures.

## Features
- Decode and print fields from:
    - Page Table Entries
    - Nested Page Table Entries ( AMD NPT )
    - Extended Page Table Entries ( Intel EPT )
    - Virtual Addresses
    - Physical Addresses
    - Paging Base Descriptors ( CR3 )
- Supports 4KB, 2MB and 1GB paging formats

## Usage

You can run this tool by inputting parameters into the console or via the command line as: <Type> <Value>
- Types
  - PTE( Page Table Entry )
    - page-table-entry
    - pte
  - NPTE( Nested Page Table Entry ):
    - nested-page-table-entry
    - nested-pte
    - npte
  - EPTE( Extended Page Table Entry ):
    - extended-page-table-entry
    - extended-pte
    - epte
  - Virtual Address:
    - virtual-address
    - virtual
    - virt
    - va
  - Physical Address:
    - physical-address
    - physical
    - phys
    - pa
  - Paging Base Descriptor:
    - paging-base-descriptor
    - paging-base
    - cr3
    - pb

Value supports both hexadecimal and decimal formats, hexadecimal numbers must be prefixed with a '0x'

## Examples

paging-value-visualiser virtual-address 0x7ff6b67840be
```
Huge:
Huge.Offset: 00000000367840BE
Huge.PDPTIndex: 00000000000001DA
Huge.PML4Index: 00000000000000FF
Huge.Reserved: 0000000000000000

Large:
Large.Offset: 00000000001840BE
Large.PDIndex: 00000000000001B3
Large.PDPTIndex: 00000000000001DA
Large.PML4Index: 00000000000000FF
Large.Reserved: 0000000000000000

Small:
Small.Offset: 00000000000000BE
Small.PTIndex: 0000000000000184
Small.PDIndex: 00000000000001B3
Small.PDPTIndex: 00000000000001DA
Small.PML4Index: 00000000000000FF
Small.Reserved: 0000000000000000
```

paging-value-visualizer cr3 0x1ab23000
```
Reserved1: 0000000000000000
PageLevelWriteThrough: 0000000000000000
PageLevelCacheDisable: 0000000000000000
Reserved2: 0000000000000000
PageFrameNumber: 000000000001AB23
Reserved3: 0000000000000000
```
