#pragma once

#include <vector>

#include "drmobject.h"

namespace kms
{

struct CrtcPriv;

class Crtc : public DrmObject
{
	friend class Card;
	friend class Connector;
public:
	void print_short() const;

	const std::vector<Plane*>& get_possible_planes() const { return m_possible_planes; }

	int set_mode(Connector* conn, Framebuffer& fb, const Videomode& mode);

	int set_plane(Plane *plane, Framebuffer &fb,
		      int32_t dst_x, int32_t dst_y, uint32_t dst_w, uint32_t dst_h,
		      float src_x, float src_y, float src_w, float src_h);

	int page_flip(Framebuffer& fb, void *data);
	int page_flip(Framebuffer& fb, PageFlipHandlerBase* data) { return page_flip(fb, (void*)data); }
private:
	Crtc(Card& card, uint32_t id, uint32_t idx);
	~Crtc();

	void setup();
	void restore_mode(Connector *conn);

	CrtcPriv* m_priv;

	std::vector<Plane*> m_possible_planes;
};
}
