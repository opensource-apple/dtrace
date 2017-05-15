/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License, Version 1.0 only
 * (the "License").  You may not use this file except in compliance
 * with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */
/*	Copyright (c) 1988 AT&T	*/
/*	  All Rights Reserved  	*/


/*
 * Copyright (c) 1998 by Sun Microsystems, Inc.
 * All rights reserved.
 */

#pragma ident	"@(#)flag.c	1.10	05/06/08 SMI" 	/* SVr4.0 1.6	*/

// XXX_PRAGMA_WEAK #pragma weak	elf_flagdata = _elf_flagdata
// XXX_PRAGMA_WEAK #pragma weak	elf_flagehdr = _elf_flagehdr
// XXX_PRAGMA_WEAK #pragma weak	elf_flagelf = _elf_flagelf
// XXX_PRAGMA_WEAK #pragma weak	elf_flagphdr = _elf_flagphdr
// XXX_PRAGMA_WEAK #pragma weak	elf_flagscn = _elf_flagscn
// XXX_PRAGMA_WEAK #pragma weak	elf_flagshdr = _elf_flagshdr


#include "syn.h"
#include "libelf.h"
#include "decl.h"
#include "msg.h"


unsigned
elf_flagdata(Elf_Data * data, Elf_Cmd cmd, unsigned flags)
{
	unsigned	rc = 0;
	Elf *		elf;
	Elf_Scn *	scn;
	Dnode *		d;

	if (data == 0)
		return (0);
	d = (Dnode *) data;
	scn = d->db_scn;
	elf = scn->s_elf;

	READLOCKS(elf, scn)

	if (cmd == ELF_C_SET) {
		rc = d->db_uflags |= flags;
	} else if (cmd == ELF_C_CLR) {
		rc = d->db_uflags &= ~flags;
	} else
		_elf_seterr(EREQ_FLAG, 0);
	READUNLOCKS(elf, scn)
	return (rc);
}


unsigned int
elf_flagehdr(Elf * elf, Elf_Cmd cmd, unsigned flags)
{
	int	rc;
	if (elf == 0)
		return (0);
	if (cmd == ELF_C_SET) {
		ELFWLOCK(elf)
		rc = elf->ed_ehflags |= flags;
		ELFUNLOCK(elf)
		return (rc);
	}
	if (cmd == ELF_C_CLR) {
		ELFWLOCK(elf)
		rc = elf->ed_ehflags &= ~flags;
		ELFUNLOCK(elf)
		return (rc);
	}
	_elf_seterr(EREQ_FLAG, 0);
	return (0);
}


unsigned
elf_flagelf(Elf * elf, Elf_Cmd cmd, unsigned flags)
{
	int	rc;
	if (elf == 0)
		return (0);
	if (cmd == ELF_C_SET) {
		ELFWLOCK(elf)
		rc = elf->ed_uflags |= flags;
		ELFUNLOCK(elf)
		return (rc);
	}
	if (cmd == ELF_C_CLR) {
		ELFWLOCK(elf)
		rc = elf->ed_uflags &= ~flags;
		ELFUNLOCK(elf)
		return (rc);
	}
	_elf_seterr(EREQ_FLAG, 0);
	return (0);
}


unsigned
elf_flagphdr(Elf * elf, Elf_Cmd cmd, unsigned flags)
{
	int	rc;
	if (elf == 0)
		return (0);
	if (cmd == ELF_C_SET) {
		ELFWLOCK(elf);
		rc = elf->ed_phflags |= flags;
		ELFUNLOCK(elf);
		return (rc);
	}
	if (cmd == ELF_C_CLR) {
		ELFWLOCK(elf);
		rc = elf->ed_phflags &= ~flags;
		ELFUNLOCK(elf);
		return (rc);
	}
	_elf_seterr(EREQ_FLAG, 0);
	return (0);
}


unsigned
elf_flagscn(Elf_Scn * scn, Elf_Cmd cmd, unsigned flags)
{
	unsigned	rc;
	Elf *		elf;

	if (scn == 0)
		return (0);

	elf = scn->s_elf;
	if (cmd == ELF_C_SET) {
		READLOCKS(elf, scn)
		rc = scn->s_uflags |= flags;
		READUNLOCKS(elf, scn)
		return (rc);
	}
	if (cmd == ELF_C_CLR) {
		READLOCKS(elf, scn)
		rc = scn->s_uflags &= ~flags;
		READUNLOCKS(elf, scn)
		return (rc);
	}
	_elf_seterr(EREQ_FLAG, 0);
	return (0);
}


unsigned
elf_flagshdr(Elf_Scn * scn, Elf_Cmd cmd, unsigned flags)
{
	unsigned	rc;
	Elf *		elf;
	if (scn == 0)
		return (0);

	elf = scn->s_elf;
	if (cmd == ELF_C_SET) {
		READLOCKS(elf, scn)
		rc = scn->s_shflags |= flags;
		READUNLOCKS(elf, scn)
		return (rc);
	}
	if (cmd == ELF_C_CLR) {
		READLOCKS(elf, scn)
		rc = scn->s_shflags &= ~flags;
		READUNLOCKS(elf, scn)
		return (rc);
	}
	_elf_seterr(EREQ_FLAG, 0);
	return (0);
}
