This is the Pascal source of a public domain Pascal compiler and
interpreter. The entire code is documented in the book:
	Pascal Implementation
	by Steven Pemberton and Martin Daniels
	published by Ellis Horwood, Chichester, UK,
(also available in Japanese).
It was distributed by John Wiley in other countries, but now that
Prentice Hall has taken over Ellis Horwood, that may have changed.

Steven Pemberton is contactable by email as steven@cwi.nl.

The code here is slightly different from that in the book, but the
line numbers have been kept the same.  The changes were to allow
modern Pascal compilers to compile the source (there were some slight
laxities in the original code).

The type marktype is added for the parameters of the routines mark and
release:
    76c76
    < 
    ---
    >      marktype= ^integer;

The type setty (which represents set types) is added for the new type
compatibility rules of ISO Pascal:
    95c95
    < 
    ---
    >      setty = set of setlow..sethigh;
    100c100
    <                          pset: (pval: set of setlow..sethigh);
    ---
    >                          pset: (pval: setty);

Missing variant parts:
    123c123
    <                                   declared: (fconst: ctp));
    ---
    >                                   declared: (fconst: ctp); standard: ());
    145a146
    >                      types: ();
    149,150c150
    <                      proc,
    <                      func:  (case pfdeckind: declkind of
    ---
    >                      proc, func:  (case pfdeckind: declkind of
    154,155c154,155
    <                                            actual: (forwdecl, extern:
    <                                                     boolean)))
    ---
    >                                            actual: (forwdecl, extern: boolean);
    >                                            formal: ()))

Pcom has the files prr and prd as standard identifiers. You have to
declare them for other compilers:
    193d192
    < 
    194a194
    >     prr: text; (* comment this out when compiling with pcom *)
    299d298
    < 

Other compilers don't have the routines mark and release. Their
effective semantics are null; you just waste heap:
    300a300,301
    >   procedure mark(var p: marktype); begin end;
    >   procedure release(p: marktype); begin end;
    302d302
    < 

Output the line number with error messages, so that if the listing
option has been switched off, you still know which line is in error:
    307c307
    <       begin write(output,' ****  ':15);
    ---
    >       begin write(output,linecount:6,' ****  ':9);

Accept tabs as white-space as well:
    398c398
    <     repeat while (ch = ' ') and not eol do nextch;
    ---
    >     repeat while ((ch = ' ') or (ch = '	')) and not eol do nextch;

Jumping from the then part of an if into the else part is not allowed;
fix cases like 1..10 in another way:
    429c429
    <           if (ch = '.') or (ch = 'e') then
    ---
    >           if ((ch = '.') and (input^ <> '.')) or (ch = 'e') then
    434c434
    <                       nextch; if ch = '.' then begin ch := ':'; goto 3 end;
    ---
    >                       nextch; (*if ch = '.' then begin ch := ':'; goto 3 end;*)

Fix modern type mismatches:
    668c668
    <   procedure align(fsp: stp; var flc: integer);
    ---
    >   procedure align(fsp: stp; var flc: addrrange);

An identifier misspelled after the 8th character:
    872c872
    <           if sy = stringconstsy then
    ---
    >           if sy = stringconst then

Unused variables, and new type names:
    1529,1531c1529,1531
    <       var oldlev: 0..maxlevel; lsy: symbol; lcp,lcp1: ctp; lsp: stp;
    <           forw: boolean; oldtop: disprange; parcnt: integer;
    <           llc,lcm: addrrange; lbname: integer; markp: ^integer;
    ---
    >       var oldlev: 0..maxlevel; lcp,lcp1: ctp; lsp: stp;
    >           forw: boolean; oldtop: disprange;
    >           llc,lcm: addrrange; lbname: integer; markp: marktype;
    1535c1535
    <           llc: addrrange; count,lsize: integer;
    ---
    >           llc,lsize: addrrange; count: integer;
    1819c1819
    <           i, entname, segsize: integer;
    ---
    >           entname, segsize: integer;
    2087c2087
    <         var lattr: attr; lcp: ctp; lsize,lmin,lmax: integer;
    ---
    >         var lattr: attr; lcp: ctp; lsize: addrrange; lmin,lmax: integer;
    2248c2248
    <             var lcp:ctp; llev:levrange; laddr:addrrange;
    ---
    >             var llev:levrange; laddr:addrrange;
    2306c2306
    <                 lcp:ctp; llev:levrange; laddr,len:addrrange;
    ---
    >                 llev:levrange; laddr,len:addrrange;
    2456,2457c2456,2457
    <             var lsp,lsp1: stp; varts,lmin,lmax: integer;
    <                 lsize,lsz: addrrange; lval: valu;
    ---
    >             var lsp,lsp1: stp; varts: integer;
    >                 lsize: addrrange; lval: valu;
    2750c2750
    <                     cstpart: set of 0..47; lsp: stp;
    ---
    >                     cstpart: setty; lsp: stp;

Unix pc can't cope with this line:
    2926c2926
    <             (*/*)     rdiv: begin
    ---
    >             (* / *)   rdiv: begin

More unused variables:
    3318c3318
    <           var lattr: attr; lsp: stp;  lsy: symbol;
    ---
    >           var lattr: attr;  lsy: symbol;
    3642c3642
    <     var sp: stp;
    ---
    > 

Produce code as default:
    3800c3800
    <     prtables := false; list := true; prcode := false; debug := true;
    ---
    >     prtables := false; list := true; prcode := true; debug := true;

Unused variable:
    3868c3868
    <       var i: integer; ch: char;
    ---
    >       var i: integer;

Other compilers need to rewrite prr before using it:
    3995,3996c3995,3996
    <   (*compile:*)
    <   (**********)
    ---
    >   (*compile:*) rewrite(prr); (*comment this out when compiling with pcom *)
    >   (**********)

Differences in the interpreter are minimal: a set type has been added:

    45a46
    >       settype     = set of 0..58;
    63c64
    <                                 sett       :(vs :set of 0..47);
    ---
    >                                 sett       :(vs :settype);
    225c226
    <       var name :alfa;  b :boolean;  r :real;  s :set of 0..58;
    ---
    >       var name :alfa;  b :boolean;  r :real;  s :settype;

End of differences
