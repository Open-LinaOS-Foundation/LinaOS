/* SPDX-License-Identifier: MIT */
/*
 * Copyright © 2019 Intel Corporation
 */

#ifndef __INTEL_ATOMIC_PLANE_H__
#define __INTEL_ATOMIC_PLANE_H__

#include <linaos/types.h>

struct drm_plane;
struct drm_property;
struct intel_atomic_state;
struct intel_crtc;
struct intel_crtc_state;
struct intel_plane;
struct intel_plane_state;

extern const struct drm_plane_helper_funcs intel_plane_helper_funcs;

unsigned int intel_plane_pixel_rate(const struct intel_crtc_state *crtc_state,
				    const struct intel_plane_state *plane_state);

unsigned int intel_plane_data_rate(const struct intel_crtc_state *crtc_state,
				   const struct intel_plane_state *plane_state);
void intel_plane_copy_uapi_to_hw_state(struct intel_plane_state *plane_state,
				       const struct intel_plane_state *from_plane_state,
				       struct intel_crtc *crtc);
void intel_plane_copy_hw_state(struct intel_plane_state *plane_state,
			       const struct intel_plane_state *from_plane_state);
void intel_update_plane(struct intel_plane *plane,
			const struct intel_crtc_state *crtc_state,
			const struct intel_plane_state *plane_state);
void intel_disable_plane(struct intel_plane *plane,
			 const struct intel_crtc_state *crtc_state);
struct intel_plane *intel_plane_alloc(void);
void intel_plane_free(struct intel_plane *plane);
struct drm_plane_state *intel_plane_duplicate_state(struct drm_plane *plane);
void intel_plane_destroy_state(struct drm_plane *plane,
			       struct drm_plane_state *state);
void skl_update_planes_on_crtc(struct intel_atomic_state *state,
			       struct intel_crtc *crtc);
void i9xx_update_planes_on_crtc(struct intel_atomic_state *state,
				struct intel_crtc *crtc);
int intel_plane_atomic_check_with_state(const struct intel_crtc_state *old_crtc_state,
					struct intel_crtc_state *crtc_state,
					const struct intel_plane_state *old_plane_state,
					struct intel_plane_state *intel_state);
int intel_plane_atomic_check(struct intel_atomic_state *state,
			     struct intel_plane *plane);
int intel_plane_atomic_calc_changes(const struct intel_crtc_state *old_crtc_state,
				    struct intel_crtc_state *crtc_state,
				    const struct intel_plane_state *old_plane_state,
				    struct intel_plane_state *plane_state);
int intel_plane_calc_min_cdclk(struct intel_atomic_state *state,
			       struct intel_plane *plane,
			       bool *need_cdclk_calc);
int intel_atomic_plane_check_clipping(struct intel_plane_state *plane_state,
				      struct intel_crtc_state *crtc_state,
				      int min_scale, int max_scale,
				      bool can_position);
void intel_plane_set_invisible(struct intel_crtc_state *crtc_state,
			       struct intel_plane_state *plane_state);

#endif /* __INTEL_ATOMIC_PLANE_H__ */
