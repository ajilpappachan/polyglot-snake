using System.Diagnostics;

namespace cs_snake
{
    public class GameObjectMan
    {
        private static GameObjectMan? sInstance;

        public static void Init()
        {
            Debug.Assert(sInstance == null);
            sInstance = new GameObjectMan();
        }

        public static void Destroy()
        {
            Debug.Assert(sInstance != null);
            sInstance.privDestroy();
            sInstance = null;
        }

        public static void Add(GameObject go)
        {
            Debug.Assert(sInstance != null);
            sInstance.privAdd(go);
        }

        public static GameObject Get(string name)
        {
            Debug.Assert(sInstance != null);
            return sInstance.privGet(name);
        }

        public static void Remove(string name)
        {
            Debug.Assert(sInstance != null);
            sInstance.privRemove(name);
        }

        public static void Update(float deltatime)
        {
            Debug.Assert(sInstance != null);
            sInstance.privUpdate(deltatime);
        }

        public static void Draw()
        {
            Debug.Assert(sInstance != null);
            sInstance.privDraw();
        }

        private Dictionary<string, GameObject> gameObjects;

        private GameObjectMan()
        {
            gameObjects = new Dictionary<string, GameObject>();
        }

        private void privDestroy()
        {
            // Do nothing
        }

        private void privAdd(GameObject go)
        {
            Debug.Assert(gameObjects.ContainsKey(go.name) == false);
            gameObjects.Add(go.name, go);
        }

        private GameObject privGet(string name)
        {
            Debug.Assert(gameObjects.ContainsKey(name) == true);
            return gameObjects[name];
        }

        private void privRemove(string name)
        {
            Debug.Assert(gameObjects.ContainsKey(name) == true);
            gameObjects.Remove(name);
        }

        private void privUpdate(float deltatime)
        {
            foreach (var go in gameObjects)
            {
                go.Value.Update(deltatime);
            }
        }

        private void privDraw()
        {
            foreach (var go in gameObjects)
            {
                go.Value.Draw();
            }
        }
    }
}