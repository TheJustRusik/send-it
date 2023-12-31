package dev.kenuki.sendit;

import android.content.Context;
import android.net.wifi.WifiManager;


public final class MulticastLockJniBridgeUtil
{

	private static WifiManager.MulticastLock cLock;


	private MulticastLockJniBridgeUtil()
	{
	}


	public static synchronized void acquire(Context pContext)
	{
		if (cLock == null)
		{
			WifiManager wifi = (WifiManager) pContext.getSystemService(Context.WIFI_SERVICE);
			cLock = wifi.createMulticastLock("Sendit");
			cLock.setReferenceCounted(true);
		}

		cLock.acquire();
	}


	public static synchronized void release(Context pContext)
	{
		cLock.release();
	}


}