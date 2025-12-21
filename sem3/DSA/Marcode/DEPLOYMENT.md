# 🚀 Deployment Guide for Marcode

This guide covers deploying the Marcode plagiarism detection application to various platforms.

## 📋 Pre-Deployment Checklist

Before deploying, ensure:

- ✅ All code is committed to your Git repository
- ✅ WASM files are present in `frontend/public/wasm/` (similarity_engine.wasm)
- ✅ `.gitignore` is properly configured (venv, node_modules, etc. are ignored)
- ✅ No environment variables required (everything runs client-side)
- ✅ Frontend builds successfully (`cd frontend && npm run build`)

---

## 1. Vercel Deployment (Recommended)

Vercel is the recommended platform for Next.js applications and is already configured.

### Option A: Deploy via Vercel Dashboard (Easiest)

#### Step 1: Push to GitHub
```bash
# Make sure all changes are committed
git add .
git commit -m "Ready for deployment"
git push origin main
```

#### Step 2: Connect to Vercel
1. Go to [vercel.com](https://vercel.com)
2. Sign up/Login (can use GitHub account)
3. Click **"Add New Project"**
4. Import your GitHub repository
5. Vercel will auto-detect Next.js configuration

#### Step 3: Configure Project Settings
The `vercel.json` file already has the correct configuration, but verify in Vercel dashboard:

- **Framework Preset:** Next.js
- **Root Directory:** Leave as root (or set to `frontend` if you prefer)
- **Build Command:** `cd frontend && npm install && npm run build`
- **Output Directory:** `frontend/.next`
- **Install Command:** `cd frontend && npm install`

**Note:** If you set Root Directory to `frontend`, the build commands become simpler:
- **Build Command:** `npm run build`
- **Output Directory:** `.next` (or leave default)
- **Install Command:** `npm install`

#### Step 4: Deploy
1. Click **"Deploy"**
2. Wait for build to complete (2-5 minutes)
3. Your app will be live at `your-project.vercel.app`

#### Step 5: Configure Custom Domain (Optional)
1. Go to Project Settings → Domains
2. Add your custom domain
3. Follow DNS configuration instructions

---

### Option B: Deploy via Vercel CLI

#### Step 1: Install Vercel CLI
```bash
npm install -g vercel
```

#### Step 2: Login
```bash
vercel login
```

#### Step 3: Deploy
```bash
# From project root
vercel

# Or for production deployment
vercel --prod
```

#### Step 4: Follow Prompts
- Set up and deploy? **Y**
- Which scope? (Select your account)
- Link to existing project? **N** (for first time)
- Project name? (Enter or use default)
- Directory? `frontend` (or leave as root if vercel.json handles it)

---

## 2. Netlify Deployment (Alternative)

Netlify is another excellent option for Next.js apps.

### Step 1: Create netlify.toml
Create `netlify.toml` in the project root:

```toml
[build]
  command = "cd frontend && npm install && npm run build"
  publish = "frontend/.next"

[[redirects]]
  from = "/*"
  to = "/index.html"
  status = 200

[[headers]]
  for = "/wasm/*"
  [headers.values]
    Cross-Origin-Embedder-Policy = "require-corp"
    Cross-Origin-Opener-Policy = "same-origin"
```

### Step 2: Deploy to Netlify
1. Go to [netlify.com](https://netlify.com)
2. Sign up/Login
3. Click **"Add new site"** → **"Import an existing project"**
4. Connect your GitHub repository
5. Configure:
   - **Base directory:** Leave empty or set to `frontend`
   - **Build command:** `cd frontend && npm install && npm run build`
   - **Publish directory:** `frontend/.next`
6. Click **"Deploy site"**

---

## 3. Railway Deployment

Railway is another modern deployment platform.

### Step 1: Create railway.json
Create `railway.json` in project root:

```json
{
  "$schema": "https://railway.app/railway.schema.json",
  "build": {
    "builder": "NIXPACKS"
  },
  "deploy": {
    "startCommand": "cd frontend && npm start",
    "restartPolicyType": "ON_FAILURE",
    "restartPolicyMaxRetries": 10
  }
}
```

### Step 2: Deploy
1. Go to [railway.app](https://railway.app)
2. Sign up/Login
3. Click **"New Project"** → **"Deploy from GitHub repo"**
4. Select your repository
5. Railway will auto-detect Next.js
6. Set **Start Command:** `cd frontend && npm start`

---

## 4. Traditional VPS Deployment (VPS/Cloud Server)

For deploying on your own server (DigitalOcean, AWS EC2, etc.)

### Step 1: Build the Application
```bash
cd frontend
npm install
npm run build
```

### Step 2: Install PM2 (Process Manager)
```bash
npm install -g pm2
```

### Step 3: Start the Application
```bash
cd frontend
pm2 start npm --name "marcode" -- start
pm2 save
pm2 startup
```

### Step 4: Configure Nginx (Reverse Proxy)
Create `/etc/nginx/sites-available/marcode`:

```nginx
server {
    listen 80;
    server_name your-domain.com;

    location / {
        proxy_pass http://localhost:3000;
        proxy_http_version 1.1;
        proxy_set_header Upgrade $http_upgrade;
        proxy_set_header Connection 'upgrade';
        proxy_set_header Host $host;
        proxy_cache_bypass $http_upgrade;
    }

    location /wasm/ {
        add_header Cross-Origin-Embedder-Policy "require-corp";
        add_header Cross-Origin-Opener-Policy "same-origin";
        proxy_pass http://localhost:3000;
    }
}
```

Enable the site:
```bash
sudo ln -s /etc/nginx/sites-available/marcode /etc/nginx/sites-enabled/
sudo nginx -t
sudo systemctl reload nginx
```

---

## 🔧 Troubleshooting

### Build Fails on Vercel

**Issue:** "Module not found" errors
**Solution:** Ensure all dependencies are in `frontend/package.json`

**Issue:** "WASM file not found"
**Solution:** 
- Verify `frontend/public/wasm/similarity_engine.wasm` exists
- Check that WASM files aren't in `.gitignore`

### WASM Not Loading

**Issue:** Cross-Origin errors
**Solution:** Ensure `vercel.json` or `netlify.toml` has correct headers:
```json
{
  "headers": [{
    "source": "/wasm/:path*",
    "headers": [{
      "key": "Cross-Origin-Embedder-Policy",
      "value": "require-corp"
    }]
  }]
}
```

### Build Succeeds but App Doesn't Work

**Issue:** Client-side errors
**Solution:**
- Check browser console for errors
- Verify WASM files are accessible at `/wasm/similarity_engine.wasm`
- Ensure environment variables (if any) are set correctly

---

## 📝 Environment Variables

Currently, Marcode doesn't require any environment variables as everything runs client-side.

If you add server-side features in the future, add them in:
- **Vercel:** Project Settings → Environment Variables
- **Netlify:** Site Settings → Build & Deploy → Environment
- **Railway:** Variables tab in your project

---

## 🔄 Continuous Deployment

### Automatic Deployments

Both Vercel and Netlify support automatic deployments:

- **Vercel:** Automatic on push to main branch (default)
- **Netlify:** Automatic on push to main branch (enable in site settings)

### Branch Previews

- Both platforms create preview deployments for pull requests
- Test before merging!

---

## 📊 Monitoring Your Deployment

### Vercel Analytics
- Built-in analytics available in Vercel dashboard
- View page views, performance metrics

### Error Tracking
Consider adding:
- Sentry for error tracking
- LogRocket for session replay
- Google Analytics for usage stats

---

## 🎯 Quick Start Commands

### Test Build Locally
```bash
cd frontend
npm install
npm run build
npm start
```

### Deploy to Vercel (CLI)
```bash
vercel --prod
```

### Check Deployment Status
```bash
vercel ls          # List deployments
vercel inspect     # Inspect current deployment
```

---

## ✅ Post-Deployment Checklist

After deploying:

- [ ] Test the application at the deployed URL
- [ ] Verify file upload works
- [ ] Test code comparison functionality
- [ ] Check WASM engine loads correctly
- [ ] Verify PDF export works
- [ ] Test on different browsers (Chrome, Firefox, Safari)
- [ ] Check mobile responsiveness
- [ ] Set up custom domain (if needed)
- [ ] Configure HTTPS (automatic on Vercel/Netlify)

---

## 🆘 Need Help?

- **Vercel Docs:** https://vercel.com/docs
- **Netlify Docs:** https://docs.netlify.com
- **Next.js Deployment:** https://nextjs.org/docs/deployment

---

**Recommended Platform:** Vercel (already configured and optimized for Next.js)

