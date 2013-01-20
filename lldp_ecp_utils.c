/******************************************************************************

  Implementation of ECP according to 802.1Qbg
  (c) Copyright IBM Corp. 2010, 2013

  Author(s): Thomas Richter <tmricht at linux.vnet.ibm.com>

  This program is free software; you can redistribute it and/or modify it
  under the terms and conditions of the GNU General Public License,
  version 2, as published by the Free Software Foundation.

  This program is distributed in the hope it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
  more details.

  You should have received a copy of the GNU General Public License along with
  this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.

  The full GNU General Public License is included in this distribution in
  the file called "COPYING".

******************************************************************************/

/*
 * This file contains common support utilities for the ECP protocols.
 */

#include <stdio.h>
#include <linux/if_ether.h>

#include "lldp.h"
#include "messages.h"
#include "lldp_ecp_utils.h"

extern int loglvl;			/* Global lldpad log level */

/*
 * ecp_print_frame - print raw ecp frame
 */
void ecp_print_frame(const char *ifname, char *txt, const unsigned char *buf,
		     size_t len)
{
	size_t i;
	int left = 0;
	char buffer[ETH_FRAME_LEN * 3];

	/* Only collect data when the loglvl ensures data printout */
	if (LOG_DEBUG < loglvl)
		return;
	for (i = 0; i < len; i++) {
		int c;
		c = snprintf(buffer + left, sizeof buffer - left, "%02x%c",
			     buf[i], !((i + 1) % 16) ? '\n' : ' ');
		if (c > 0 && (c < (int)sizeof buffer - left))
			left += c;
	}
	LLDPAD_DBG("%s:%s %s\n%s\n", __func__, ifname, txt, buffer);
}