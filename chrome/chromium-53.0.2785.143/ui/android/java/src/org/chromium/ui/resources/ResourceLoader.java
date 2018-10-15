// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

package org.chromium.ui.resources;

/**
 * A class responsible for loading {@link Resource}s for the {@link ResourceManager}.
 */
public abstract class ResourceLoader {
    /**
     * A callback that specifies when a {@link Resource} has been loaded and can be exposed to the
     * CC layer.
     */
    public interface ResourceLoaderCallback {
        /**
         * Called when a resource as finished loading.  Note that it is up to the caller to recycle
         * any {@link android.graphics.Bitmap}s or clean up any state after making this call.
         * @param resType  The {@link ResourceType} that loaded the resource.
         * @param resId    The Android id of the loaded resource.
         * @param resource The {@link Resource} of the resource, or {@code null} if one could
         *                 not be loaded.
         */
        void onResourceLoaded(int resType, int resId, Resource resource);
    }

    private final int mResourceType;
    private final ResourceLoaderCallback mCallback;

    /**
     * Creates an instance of a {@link ResourceLoader}.
     * @param resourceType The resource type category this {@link ResourceLoader} is loading.
     * @param callback     The {@link ResourceLoaderCallback} to notify when a {@link Resource} is
     *                     loaded.
     */
    public ResourceLoader(int resourceType, ResourceLoaderCallback callback) {
        mResourceType = resourceType;
        mCallback = callback;
    }

    /**
     * @return What resource type this {@link ResourceLoader} is responsible for loading.
     */
    public int getResourceType() {
        return mResourceType;
    }

    /**
     * Requests that a resource specified by {@code resId} be loaded from this
     * {@link ResourceLoader}.  This may or may not actually load the resource and notify the
     * {@link ResourceLoaderCallback} depending on the internal behavior of the particular loader.
     * @param resId The id of the {@link Resource} to load.
     */
    public abstract void loadResource(int resId);

    /**
     * Requests that a resource be pre-loaded.  This will typically happen asynchronously.
     * @param resId The id of the {@link Resource} to load.
     */
    public abstract void preloadResource(int resId);

    /**
     * A helper method for subclasses to notify that the {@link Resource} specified by {@code resId}
     * is done loading.
     * @param resId    The id of the {@link Resource} that loaded or failed.
     * @param resource The {@link Resource}, or {@code null} if the load failed.
     */
    protected void notifyLoadFinished(int resId, Resource resource) {
        if (mCallback != null) mCallback.onResourceLoaded(getResourceType(), resId, resource);
    }
}
