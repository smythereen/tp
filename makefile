# SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later
# Copyright (c) 2011-2026 John R. Smythe Jr.
#

#
#	Global Definitions
#

include		../rules.mak

#
#	Unit and Common Header Definitions
#

CHDRS =	$(HDR)/$(UNIT).h	\
	$(HDR)/$(UNIT)d.h	\
	$(HDR)/$(UNIT)h.h	\
	$(HDR)/$(UNIT)s.h

#
#	Unit's Library Definitions
#

LIBRARIES =	-lmio	\
		-lnow	\
		-lmap	\
		-lsem	\
		-lfar	\
		-lsys

LIBRARY1 :=      $(LIB)/lib$(UNIT)d.a
LIBRARY2 :=      $(LIB)/lib$(UNIT)h.a
LIBRARY3 :=      $(LIB)/lib$(UNIT)s.a

library::
	@ln -sf $(LIBRARY) $(LIBRARY1);
	@ln -sf $(LIBRARY) $(LIBRARY2);
	@ln -sf $(LIBRARY) $(LIBRARY3);

#
#	Product Definitions
#


#
#	Global Targets
#

include		../targets.mak

#
#	Unit's Targets
#

clean cleanup::
	@-rm -f $(LIBRARY1) ;
	@-rm -f $(LIBRARY2) ;
	@-rm -f $(LIBRARY3) ;

#
#	Include	Object Dependency Files
#

include	.depend
