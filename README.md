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
