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

paging-value-visualiser virtual-address 0xfffff80000001234
```
Huge:
Huge.Offset: 0000000000001234
Huge.PDPTIndex: 0000000000000000
Huge.PML4Index: 00000000000001F0
Huge.Reserved: 000000000000FFFF

Large:
Large.Offset: 0000000000001234
Large.PDIndex: 0000000000000000
Large.PDPTIndex: 0000000000000000
Large.PML4Index: 00000000000001F0
Large.Reserved: 000000000000FFFF

Small:
Small.Offset: 0000000000000234
Small.PTIndex: 0000000000000001
Small.PDIndex: 0000000000000000
Small.PDPTIndex: 0000000000000000
Small.PML4Index: 00000000000001F0
Small.Reserved: 000000000000FFFF
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
