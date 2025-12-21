# 🔧 Fixing 404 NOT_FOUND Error

## Problem
You're getting a `404: NOT_FOUND` error on Vercel.

## Solution: Set Root Directory to `frontend`

The issue is that Vercel needs to know where your Next.js app is located. 

### Steps to Fix:

1. **Go to your Vercel project settings**
   - Open your project dashboard on Vercel
   - Go to **Settings** → **General**

2. **Update Root Directory:**
   - Find **Root Directory** setting
   - Change it from blank to: **`frontend`**
   - Click **Save**

3. **Update Build Settings (if needed):**
   - Go to **Settings** → **Build & Development Settings**
   - Verify these settings:
     - **Framework Preset:** Next.js
     - **Root Directory:** `frontend`
     - **Build Command:** `npm run build` (should auto-detect)
     - **Output Directory:** `.next` (should auto-detect)
     - **Install Command:** `npm install` (should auto-detect)

4. **Redeploy:**
   - Go to **Deployments** tab
   - Click the **"..."** menu on the latest deployment
   - Click **"Redeploy"**
   - OR push a new commit to trigger a new deployment

## Alternative: If You Want Root Directory Empty

If you prefer to keep root directory empty, you need to update Vercel settings manually:

- **Root Directory:** Leave empty
- **Build Command:** `cd frontend && npm install && npm run build`
- **Output Directory:** `frontend/.next`
- **Install Command:** `cd frontend && npm install`

## Why This Happens

Next.js expects to be at the project root. When your Next.js app is in a subdirectory (`frontend/`), Vercel needs to know:
1. Where to find the `package.json`
2. Where to run the build command
3. Where to look for the `.next` output folder

Setting Root Directory to `frontend` tells Vercel: "Treat the `frontend` folder as the project root for this Next.js app."

## Verification

After redeploying, you should see:
- ✅ Build succeeds
- ✅ No 404 errors
- ✅ Home page loads at `your-project.vercel.app`
- ✅ `/compare` page works

---

**Updated `vercel.json`**: The file has been simplified for when root directory is set to `frontend`. Both `vercel.json` files (root and frontend) are now configured correctly.

